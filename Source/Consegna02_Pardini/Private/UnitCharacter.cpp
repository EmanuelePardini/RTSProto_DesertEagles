// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCharacter.h"

#include "AttackComponent.h"
#include "UnitAnim.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AUnitCharacter::AUnitCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SelectionMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectionMesh");
	SelectionMesh->SetupAttachment(RootComponent);
	SelectionMesh->SetHiddenInGame(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	AttackComponent = CreateDefaultSubobject<UAttackComponent>("AttackComponent");
	AttackComponent->OnAttackChanged.AddDynamic(this, &AUnitCharacter::SetIsAttacking);

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
	HealthWidget->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AUnitCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Animation Settings
	Anim = Cast<UUnitAnim>(GetMesh()->GetAnimInstance());

	//HealthWidget Settings
	if (HealthWidget && HealthWidget->GetUserWidgetObject())
	{
		HealthProgressBar = Cast<UProgressBar>(HealthWidget->GetUserWidgetObject()->GetWidgetFromName(ProgressBarId));
		if (HealthProgressBar)
		{
			UpdateHealthBar();
			HealthComponent->OnHealthChanged.AddDynamic(this, &AUnitCharacter::UpdateHealthBar);
		}
	}
}

// Called every frame
void AUnitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(Anim) Anim->Animate(this);

}

void AUnitCharacter::OnSelect()
{
	SelectionMesh->SetHiddenInGame(false);
}

void AUnitCharacter::OnDeselect()
{
	SelectionMesh->SetHiddenInGame(true);
}

void AUnitCharacter::UpdateHealthBar()
{
	if (!HealthProgressBar) return;
	float HealthPercentage = static_cast<float>(HealthComponent->ActualHealth) / HealthComponent->MaxHealth;
	HealthProgressBar->SetPercent(HealthPercentage);
}

void AUnitCharacter::SetIsAttacking(bool NewState)
{
	IsAttacking = NewState;
}
