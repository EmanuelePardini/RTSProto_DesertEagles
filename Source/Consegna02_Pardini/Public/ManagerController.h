// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ManagerPawn.h"
#include "ManagerController.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA02_PARDINI_API AManagerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UInputMappingContext* IMC;
	UPROPERTY(VisibleAnywhere)
	AManagerPawn* ManagerPawn;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UManagerInputData* InputData;
	
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

	void ZoomManager(const FInputActionValue& Value);
	void MoveManager();
	void MoveUnits(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void DeselectUnits(const FInputActionValue& Value);
	
	void ShowCursor();
};
