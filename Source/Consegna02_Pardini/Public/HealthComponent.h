// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONSEGNA02_PARDINI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHealth = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int ActualHealth;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);
	UPROPERTY(EditAnywhere)
	FOnHealthChanged OnHealthChanged;
	

	UPROPERTY(EditAnywhere)
	float HealthRecoveryDelay = 30.f;
	UPROPERTY(VisibleAnywhere)
	float HealthRecoveryTimer = 0.f;
	UPROPERTY(EditAnywhere)
	int HealthRecoveryAmount = 10;

	
	UFUNCTION(BlueprintCallable)
	void DecrementHealth(int DamageAmount);
	UFUNCTION()
	void Die();
	
protected:
	// Called when the game starts
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void IncrementHealth(int RecoveryAmount);
	UFUNCTION(BlueprintCallable)
	void RecoveryTimer(float DeltaTime);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
