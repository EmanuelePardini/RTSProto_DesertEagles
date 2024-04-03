// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "UnitCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "ManagerPawn.generated.h"

UCLASS(Blueprintable, BlueprintType)
class CONSEGNA02_PARDINI_API AManagerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AManagerPawn();
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	//If is not selection then is placeActor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool SelectionClickMode = true; //Changed Dynamically on UI BP
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;  //Changed Dynamically on UI BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraMovementSpeed = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraZoomSpeed = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AUnitCharacter*> PossessedUnits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AcceptanceRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScreenEdgeThreshold = 50.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveManager();
	void ZoomManager(const FInputActionValue& Value);
	void MoveUnits();
	void Interact();
	void SelectUnits();
	void SpawnActorAtLocation(TSubclassOf<AActor> AcToSpawn);
	void DeselectUnits();
};
