// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GetNextLocation.h"

#include "EnemyAIController.h"
#include "UnitCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTT_GetNextLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	AEnemyAIController* AIController = Cast<AEnemyAIController>(Controller);
	
	if (!AIController) 
		return EBTNodeResult::Failed;
	
	ACharacter* Character = Cast<AUnitCharacter>(AIController->GetPawn());
	if (!Character) 
		return EBTNodeResult::Failed;

	AEnemyAIController* Owner = Cast<AEnemyAIController>(Character->GetController());
	if (!Owner) 
		return EBTNodeResult::Failed;
	
	// Getting all enemy pawns in the world
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitCharacter::StaticClass(), FoundActors);
	FVector EnemyLoc = Owner->K2_GetActorLocation();
	FVector NextDestination = FVector::ZeroVector; // Initializing with zero vector
	float NearestDistance = 20000; // Max float value to find minimum distance
	for (AActor* Actor : FoundActors)
	{
		FVector UnitLoc = Actor->GetActorLocation();
		
		AUnitCharacter* Unit = Cast<AUnitCharacter>(Actor);
		float Distance = FVector::Dist(EnemyLoc, UnitLoc);
		if (Distance < NearestDistance)
		{
			NextDestination = FVector(UnitLoc.X, UnitLoc.Y, EnemyLoc.Z);
			NearestDistance= Distance;
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(DistanceKey.SelectedKeyName, NearestDistance);
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, Unit);
			AIController->Target = Unit;
		}
	}
	
	NextDestination = FVector(NextDestination.X, NextDestination.Y, EnemyLoc.Z);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(DestinationKey.SelectedKeyName, NextDestination);
	return EBTNodeResult::Succeeded;
}
