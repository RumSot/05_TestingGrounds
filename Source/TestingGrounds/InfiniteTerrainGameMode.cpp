// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Kismet/KismetSystemLibrary.h"		// UKismetSystemLibrary::PrintString
#include "EngineUtils.h"
#include "ActorPool.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	// TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());		// alternative syntax

	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator) 
	{
		AddToPool(*VolumeIterator);		// The contents of the VolumeIterator is a pointer to a ANavMeshBoundsVolume
		++VolumeIterator;				// Note ++VolumeIterator is overloaded but not VolumeIterator++
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}

void AInfiniteTerrainGameMode::UpdateScore()
{
	++Score;
	FString CurrentScore = FString::Printf(TEXT("Score: %d"), Score);
	UKismetSystemLibrary::PrintString(GetWorld(), CurrentScore);
}
