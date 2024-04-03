// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComponent;
	if(Behavior)
	{
		UseBlackboard(Behavior->BlackboardAsset, BlackboardComponent);
		Blackboard = BlackboardComponent;
	
		RunBehaviorTree(Behavior);
	}
}
