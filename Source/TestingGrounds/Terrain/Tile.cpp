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

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int i = 0; i < NumberToSpawn; i++) {
		auto SpawnPoint = FMath::RandPointInBox(Bounds);
		auto Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	CastSphere(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult OUT HitResult;	// Not used
	
	bool HasHit = GetWorld()->SweepSingleByChannel(OUT HitResult,
		Location, 
		Location,
		FQuat::Identity,	// zero rotation (i.e. will have no effect)
		ECollisionChannel::ECC_GameTraceChannel2,	// Spawn trace channel set up in Unreal Project Settings
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColour = (HasHit) ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColour, true, 100);

	return HasHit;
}

