// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTINGGROUNDS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrassComponent();

	// The extents of the spawning area
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FBox SpawningBox;

	// The number of instances to be spawned
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 SpawnCount = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SpawnGrass();
};
