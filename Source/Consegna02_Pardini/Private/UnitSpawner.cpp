// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawner.h"

// Sets default values
AUnitSpawner::AUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>("Spawn Collider");
	Collider->SetupAttachment(RootComponent);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AUnitSpawner::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AUnitSpawner::OnEndOverlap);

}

// Called when the game starts or when spawned
void AUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsActive) ManageSpawn(DeltaTime);
}

void AUnitSpawner::ManageSpawn(float DeltaTime)
{
	if(!UnitToSpawn || !ControllerToSpawn) return;
	
	SpawnTimer += DeltaTime;
	
	if (SpawnTimer >= SpawnDelay)
	{
		SpawnTimer = 0;
        
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		ACharacter* Character= GetWorld()->SpawnActor<ACharacter>(UnitToSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);
		AController* Controller = GetWorld()->SpawnActor<AController>(ControllerToSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);
		
		Controller->Possess(Character);
	}
}

void AUnitSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnitCharacter* ActivatorUnit = Cast<AUnitCharacter>(OtherActor);
	//If is the same type of the Unit to spawn then can activate
	if (ActivatorUnit && ActivatorUnit->IsA(*UnitToSpawn)) Activate();
}

void AUnitSpawner::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AUnitCharacter* ActivatorUnit = Cast<AUnitCharacter>(OtherActor);
	//If is the same type of the Unit to spawn then can activate
	if (ActivatorUnit && ActivatorUnit->IsA(*UnitToSpawn)) Deactivate();
}

