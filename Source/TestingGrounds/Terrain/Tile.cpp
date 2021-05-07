// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int i = 0; i < NumberToSpawn; i++) {
		FVector OUT SpawnPoint;
		auto RandomScale = FMath::RandRange(MinScale, MaxScale);

		auto FoundLocation = FindEmptyLocation(OUT SpawnPoint, Radius * RandomScale);

		if (FoundLocation) {
			auto RandomRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandomScale);
		}
		//else {
		//	UE_LOG(LogTemp, Warning, TEXT("Couldn't find an empty location!"));
		//}
	}
}

bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	auto Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);

	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


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

