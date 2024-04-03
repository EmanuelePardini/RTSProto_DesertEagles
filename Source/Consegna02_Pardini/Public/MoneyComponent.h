// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoneyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONSEGNA02_PARDINI_API UMoneyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoneyComponent();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Economy")
	int Money = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Economy")
	int InitialMoney = 10000;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyChanged, int, NewMoneyAmount);
	FOnMoneyChanged OnMoneyChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void SetupInitialMoney();
	UFUNCTION()
	void AddMoney(int Amount);
	UFUNCTION()
	void RemoveMoney(int Amount);
	UFUNCTION()
	bool CanAfford(int Amount);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	int GetMoney() const { return Money; }
		
};
