// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GetNextLocation.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA02_PARDINI_API UBTT_GetNextLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category ="Setup")
	FBlackboardKeySelector DestinationKey;
	UPROPERTY(EditAnywhere, Category ="Setup")
	FBlackboardKeySelector DistanceKey;
	UPROPERTY(EditAnywhere, Category ="Setup")
	FBlackboardKeySelector TargetKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
