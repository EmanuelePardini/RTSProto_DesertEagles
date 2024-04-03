// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ManagerInputData.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA02_PARDINI_API UManagerInputData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	class UInputAction* Interact;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	class UInputAction* DeselectUnits;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* MoveUnit;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* MoveManager;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* ZoomManager;
};
