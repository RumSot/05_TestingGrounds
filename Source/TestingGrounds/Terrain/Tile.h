// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

	UFUNCTION(BlueprintCallable, Category = "Props")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	 * Minimum corner on the tile, default value set in constructor.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	/**
	 * Maximum corner on the tile, default value set in constructor
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

	/**
	* Default value set in constructor.
	*/
	UPROPERTY(EditDefaultsOnly,  Category = "Navigation")
	FVector NavigationBoundsOffset;



private:
	void PositionNavMeshBoundsVolume();

	bool IsLocationEmpty(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);	// Rotation is around the z-axis only

	UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};
