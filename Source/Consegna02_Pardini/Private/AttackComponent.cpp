// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "UnitAnim.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	AttackTimer = AttackDelay;
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageAttack(DeltaTime);
}

void UAttackComponent::ManageAttack(float DeltaTime)
{
	// Increment the attack timer
	AttackTimer += DeltaTime;

	// If attack timer is less than attack delay, exit the function
	if (AttackTimer < AttackDelay) 
	return;
	
	// Find all characters within the specified range
	TArray<AActor*> FoundActors;
	for (auto const TargetClass : TargetClasses)
	{
		TArray<AActor*> ActorsOfClass;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, ActorsOfClass);
		FoundActors.Append(ActorsOfClass);
	}
	
	// Find the closest enemy
	AUnitCharacter* ClosestEnemy = nullptr;
	float ClosestDistanceSquared = FMath::Square(AttackRange);
	FVector OwnerLocation = GetOwner()->GetActorLocation();

	for (AActor* Actor : FoundActors)
	{
		AUnitCharacter* Unit = Cast<AUnitCharacter>(Actor);
		if (Actor != GetOwner()) // Ensure the actor is not self
		{
			float DistanceSquared = FVector::DistSquared(Actor->GetActorLocation(), OwnerLocation);

			if (DistanceSquared < ClosestDistanceSquared)
			{
				ClosestDistanceSquared = DistanceSquared;
				ClosestEnemy = Unit;
			}
		}
	}
	
	AUnitCharacter* Owner = Cast<AUnitCharacter>(GetOwner());
	float OwnerSpeed = Owner->GetVelocity().Size();
	
	// If there's an enemy to attack and the owner is a Unit, perform the attack
	if (Owner && OwnerSpeed==0 && ClosestEnemy)
	{
		//Play Animation
		if(Owner->Anim) Owner->Anim->IsAttacking = true;
		IsAttacking = true;
		OnAttackChanged.Broadcast(IsAttacking);
		
		// Perform attack on the closest enemy
		Attack(ClosestEnemy, Owner);

		// Reset the attack timer
		AttackTimer = 0;
	}
	else
	{
		//Doesn't have anything to attack
		if(Owner->Anim) Owner->Anim->IsAttacking = false;
		IsAttacking = false;
		OnAttackChanged.Broadcast(IsAttacking);
	}
}

void UAttackComponent::Attack(AUnitCharacter* Enemy, AUnitCharacter* Owner)
{
	if (Enemy)
	{
		// Calculate the direction from owner to enemy
		FVector Direction = (Enemy->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();

		// Rotate the attacker towards the enemy
		FRotator NewRotation = Direction.Rotation();
		Owner->SetActorRotation(NewRotation);

		// Set up parameters for the line trace
		FCollisionQueryParams TraceParams(FName(TEXT("LineTraceParams")), true, Owner);
		TraceParams.bReturnPhysicalMaterial = false;

		// Perform line trace to see if there are obstacles between attacker and enemy
		FHitResult HitResult;
		FVector StartTrace = Owner->GetActorLocation();
		FVector EndTrace = Enemy->GetActorLocation();
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams);

		if (!bHit || HitResult.GetActor() == Enemy)
		{
			// If there are no obstacles between attacker and enemy, decrement enemy's health
			if (Enemy->HealthComponent)
			{
				Enemy->HealthComponent->DecrementHealth(Damage);
			}
		}
	}
}

