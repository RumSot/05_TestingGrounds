// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolume = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
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
	UE_LOG(LogTemp, Warning, TEXT("Volume Added: %s"), *VolumeToAdd->GetName());
}
