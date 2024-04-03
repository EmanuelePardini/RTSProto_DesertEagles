// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitCharacter.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA02_PARDINI_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AUnitCharacter* Target;
	
private:
	UPROPERTY(EditAnywhere, Category="Setup")
	UBehaviorTree* Behavior;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
