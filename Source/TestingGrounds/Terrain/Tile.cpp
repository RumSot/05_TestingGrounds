// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "../InfiniteTerrainGameMode.h"
#include "../ActorPool.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "Math/Color.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include <algorithm>

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}

void ATile::TileConquered()
{
	if (TileNotConquered)
	{
		auto GameMode = Cast<AInfiniteTerrainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!GameMode) return;

		GameMode->UpdateScore();
		TileNotConquered = false;
	}
}

void ATile::SetPool(UActorPool* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool."), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}"), *(this->GetName()), *(NavMeshBoundsVolume->GetName()));
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	NavSystem->Build();
}


void ATile::SpawnActors(TSubclassOf<AActor> ToSpawn, FSpawnSeeds SpawnSeeds)
{
	
	auto SpawnPositions = GenerateSpawnPositions(SpawnSeeds);

	for (auto SpawnPosition : SpawnPositions) 
	{
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

void ATile::SpawnAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnSeeds SpawnSeeds)
{
	auto SpawnPositions = GenerateSpawnPositions(SpawnSeeds);

	for (auto SpawnPosition : SpawnPositions)
	{
		PlaceAIPawn(ToSpawn, SpawnPosition);
	}
}

TArray<FSpawnPosition> ATile::GenerateSpawnPositions(FSpawnSeeds SpawnSeeds)
{
	TArray<FSpawnPosition> SpawnPositions;

	int NumberToSpawn = FMath::RandRange(SpawnSeeds.MinToSpawn, SpawnSeeds.MaxToSpawn);

	for (int i = 0; i < NumberToSpawn; i++) {
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnSeeds.MinScale, SpawnSeeds.MaxScale);
		auto FoundLocation = FindEmptyLocation(OUT SpawnPosition.Location, SpawnSeeds.Radius * SpawnPosition.Scale);

		if (FoundLocation) {
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPositions.Push(SpawnPosition);
		}
	}

	return SpawnPositions;
}

bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);

	const int MAX_ATTEMPTS = 10;

	for (int i = 0; i < MAX_ATTEMPTS; i++) {
		auto CandidateLocation = FMath::RandPointInBox(Bounds);
		if (IsLocationEmpty(CandidateLocation, Radius)) {
			OutLocation = CandidateLocation;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	auto Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);

	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	auto Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);

	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));

	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Pool->Return(NavMeshBoundsVolume);

	UE_LOG(LogTemp, Warning, TEXT("[%s] EndPlay"), *GetName());
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::IsLocationEmpty(FVector Location, float Radius)
{
	FHitResult OUT HitResult;	// Not used
	auto GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel(OUT HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,	// zero rotation (i.e. will have no effect)
		ECollisionChannel::ECC_GameTraceChannel2,	// Spawn trace channel set up in Unreal Project Settings
		FCollisionShape::MakeSphere(Radius)
	);

	//FColor ResultColour = (HasHit) ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColour, true, 100);

	return !HasHit;
}

