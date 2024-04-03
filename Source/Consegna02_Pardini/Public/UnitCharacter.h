// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "UnitCharacter.generated.h"

UCLASS()
class CONSEGNA02_PARDINI_API AUnitCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitCharacter();
	//For Selection
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSelected = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = true;
	
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAttackComponent* AttackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SelectionMesh;

	//HealthBarWidget
	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthWidget;
	UPROPERTY(VisibleAnywhere)
	UProgressBar* HealthProgressBar;
	UPROPERTY(EditAnywhere)
	FName ProgressBarId = "ProgressBar_0";

	//Particles
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ParticlesHidden = false;
	
	
	//Animations
	UPROPERTY(VisibleAnywhere)
	class UUnitAnim* Anim;
	
protected:
	UFUNCTION()
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void OnSelect();
	UFUNCTION(BlueprintCallable)
	void OnDeselect();
	UFUNCTION()
	void UpdateHealthBar();
	UFUNCTION()
	void SetIsAttacking(bool NewState);
};
