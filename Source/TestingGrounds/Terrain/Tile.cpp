// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors()
{
//	FMath::RandRange(float, float) or (int32, int32)
	FVector Min(0, -2000, 0);
	FVector Max(+4000, +2000, 0);
	FBox Bounds(Min, Max);

	for (int i = 0; i < 10; i++) {
		auto RandomPoint = FMath::RandPointInBox(Bounds);
		UE_LOG(LogTemp, Warning, TEXT("RandomPoint: %s"), *RandomPoint.ToCompactString());
	}

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

