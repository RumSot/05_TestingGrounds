// Fill out your copyright notice in the Description page of Project Settings.


#include "GrassComponent.h"



UGrassComponent::UGrassComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	for (int32 i = 0; i < SpawnCount; i++) {
		AddInstance(FTransform(FMath::RandPointInBox(SpawningBox)));
	}
}

// Called every frame
void UGrassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

