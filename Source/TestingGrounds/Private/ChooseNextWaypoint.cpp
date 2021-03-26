// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingGuard.h"	// TODO: remove if possible later
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points

	auto AIContoller = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIContoller->GetPawn();
	auto Guard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = Guard->PatrolPointsCPP;

	// Set Next Waypoint

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle Index
	auto NextWaypoint = ((++Index) % PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextWaypoint);

//	UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);

	return EBTNodeResult::Succeeded;
}
