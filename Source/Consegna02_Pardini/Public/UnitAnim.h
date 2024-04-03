// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitCharacter.h"
#include "Animation/AnimInstance.h"
#include "UnitAnim.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA02_PARDINI_API UUnitAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsWalking = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAttacking = false;

	void Animate(AUnitCharacter* Character);
	FVector GetDeltaRoot(){return ConsumeExtractedRootMotion(1).GetRootMotionTransform().GetLocation();}
};
