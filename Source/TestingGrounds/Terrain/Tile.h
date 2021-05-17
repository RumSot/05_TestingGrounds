// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

USTRUCT(BlueprintType, Category = "Seeds")
struct FSpawnSeeds
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Seeds")
	int MinToSpawn = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Seeds")
	int MaxToSpawn = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Seeds")
	float Radius = 500;

	UPROPERTY(BlueprintReadWrite, Category = "Seeds")
	float MinScale = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Seeds")
	float MaxScale = 1;
};


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

	//UFUNCTION(BlueprintCallable, Category = "Props")
	//void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnActors(TSubclassOf<AActor> ToSpawn, struct FSpawnSeeds SpawnSeeds);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnAIPawns(TSubclassOf<APawn> ToSpawn, struct FSpawnSeeds SpawnSeeds);

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

	TArray<FSpawnPosition> GenerateSpawnPositions(FSpawnSeeds SpawnSeeds);

	bool IsLocationEmpty(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);	// Rotation is around the z-axis only
	void PlaceAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};
