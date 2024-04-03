// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "UnitSpawner.generated.h"

UCLASS()
class CONSEGNA02_PARDINI_API AUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitSpawner();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AUnitCharacter> UnitToSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AController> ControllerToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable)
	bool IsActive = false;
	UPROPERTY(VisibleAnywhere)
	float SpawnTimer = 0;
	UPROPERTY(EditAnywhere)
	float SpawnDelay = 10.f;
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ManageSpawn(float DeltaTime);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	FORCEINLINE void Activate() { IsActive = true;}
	UFUNCTION()
	FORCEINLINE void Deactivate() { IsActive = false;}

};
