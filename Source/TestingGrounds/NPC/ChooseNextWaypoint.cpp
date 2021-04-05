// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO: guard against no PatrolRoute component
	// TODO: guard against no patrol points

	// Event Receive Execute AI
	auto AIContoller = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIContoller->GetPawn();

	// Get Patrol Route
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) {
		return EBTNodeResult::Failed;
	}

	// Get Patrol Points
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() == 0) {
		auto GuardsName = ControlledPawn->GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s has no patrol points."), *GuardsName);
		return EBTNodeResult::Failed;
	}
	else {
		// Set Next Waypoint
		auto BlackboardComp = OwnerComp.GetBlackboardComponent();
		auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
		BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

		// Cycle Index
		auto NextWaypoint = ((++Index) % PatrolPoints.Num());
		BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextWaypoint);
	}
	return EBTNodeResult::Succeeded;
}
