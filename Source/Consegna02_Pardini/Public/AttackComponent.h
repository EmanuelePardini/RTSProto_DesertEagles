// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitCharacter.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONSEGNA02_PARDINI_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();
	UPROPERTY(EditAnywhere)
	float AttackRange = 1500.f;
	UPROPERTY(EditAnywhere)
	int Damage = 10;
	UPROPERTY(EditAnywhere)
	bool IsAttacking = false;
	UPROPERTY(VisibleAnywhere)
	float AttackTimer = 0.f;
	UPROPERTY(EditAnywhere)
	float AttackDelay = 0.5f;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnitCharacter>> TargetClasses;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackChanged, bool, Hidden);
	UPROPERTY(EditAnywhere)
	FOnAttackChanged OnAttackChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ManageAttack(float DeltaTime);
	void Attack(AUnitCharacter* Enemy, AUnitCharacter* Owner);
};
