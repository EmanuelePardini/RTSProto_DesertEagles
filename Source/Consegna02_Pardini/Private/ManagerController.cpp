// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ManagerInputData.h"
#include "ManagerPawn.h"

void AManagerController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
		ManagerPawn = Cast<AManagerPawn>(GetPawn());
	}
	ShowCursor();
}

void AManagerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Zoom Manager
		EnhancedInputComponent->BindAction(InputData->ZoomManager, ETriggerEvent::Triggered, this, &AManagerController::ZoomManager);
		
		//Moving Units
		EnhancedInputComponent->BindAction(InputData->MoveUnit, ETriggerEvent::Triggered, this, &AManagerController::MoveUnits);
    		
		//Selecting Units
		EnhancedInputComponent->BindAction(InputData->Interact, ETriggerEvent::Triggered, this, &AManagerController::Interact);
		
		//Deselecting Units
		EnhancedInputComponent->BindAction(InputData->DeselectUnits, ETriggerEvent::Triggered, this, &AManagerController::DeselectUnits);
	}
}

void AManagerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveManager();
}

void AManagerController::MoveManager()
{
	ManagerPawn->MoveManager();
	ShowCursor();
}

void AManagerController::ZoomManager(const FInputActionValue& Value)
{
	ManagerPawn->ZoomManager(Value);
}

void AManagerController::MoveUnits(const FInputActionValue& Value)
{
	ManagerPawn->MoveUnits();
	ShowCursor();
}

void AManagerController::Interact(const FInputActionValue& Value)
{
	ManagerPawn->Interact();
	ShowCursor();
}

void AManagerController::DeselectUnits(const FInputActionValue& Value)
{
	ManagerPawn->DeselectUnits();
	ShowCursor();
}

void AManagerController::ShowCursor()
{
	bShowMouseCursor = true;
}
