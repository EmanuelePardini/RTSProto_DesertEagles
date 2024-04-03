// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyComponent.h"

// Sets default values for this component's properties
UMoneyComponent::UMoneyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoneyComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInitialMoney();
}

void UMoneyComponent::SetupInitialMoney()
{
	Money = InitialMoney;
	OnMoneyChanged.Broadcast(Money);
}


void UMoneyComponent::AddMoney(int Amount)
{
	Money += Amount;
	OnMoneyChanged.Broadcast(Money);
}

void UMoneyComponent::RemoveMoney(int Amount)
{
	if(CanAfford(Amount))
	{
		Money -= Amount;
		OnMoneyChanged.Broadcast(Money);
	}
}

bool UMoneyComponent::CanAfford(int Amount)
{
	if (Money >= Amount) return true;
	return false;
}


// Called every frame
void UMoneyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

