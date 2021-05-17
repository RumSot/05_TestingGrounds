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

	UFUNCTION(BlueprintCallable, Category = "Scoring")
	void TileConquered();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

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

	bool IsLocationEmpty(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);


	template<typename T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, struct FSpawnSeeds SpawnSeeds);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);	// Rotation is around the z-axis only
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	UActorPool* Pool;
	AActor* NavMeshBoundsVolume;

	bool TileNotConquered = true;
};

template<typename T>
inline void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FSpawnSeeds SpawnSeeds)
{
	int NumberToSpawn = FMath::RandRange(SpawnSeeds.MinToSpawn, SpawnSeeds.MaxToSpawn);

	for (int i = 0; i < NumberToSpawn; i++) {
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnSeeds.MinScale, SpawnSeeds.MaxScale);
		auto FoundLocation = FindEmptyLocation(OUT SpawnPosition.Location, SpawnSeeds.Radius * SpawnPosition.Scale);

		if (FoundLocation) {
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}
}

