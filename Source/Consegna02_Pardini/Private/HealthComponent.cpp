// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::DecrementHealth(int DamageAmount)
{
	ActualHealth -= DamageAmount;
	if(ActualHealth <= 0)
	{
		ActualHealth = 0;
		Die();
	}
	OnHealthChanged.Broadcast();
}

void UHealthComponent::Die()
{
	GetOwner()->Destroy();
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	ActualHealth = MaxHealth;
}

void UHealthComponent::IncrementHealth(int RecoveryAmount)
{
	if(ActualHealth < MaxHealth) ActualHealth += RecoveryAmount;
	if(ActualHealth > MaxHealth) ActualHealth = MaxHealth;
	OnHealthChanged.Broadcast();
}

void UHealthComponent::RecoveryTimer(float DeltaTime)
{
	HealthRecoveryTimer += DeltaTime;

	if(HealthRecoveryTimer >= HealthRecoveryDelay)
	{
		IncrementHealth(HealthRecoveryAmount);
		HealthRecoveryTimer = 0;
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RecoveryTimer(DeltaTime);
}

