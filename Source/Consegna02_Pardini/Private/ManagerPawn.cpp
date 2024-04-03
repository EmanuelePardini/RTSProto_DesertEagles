// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerPawn.h"
#include "EnemyUnitCharacter.h"
#include "AIController.h"
#include "MoneyComponent.h"
#include "NavigationSystem.h"
#include "Engine/GameViewportClient.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AManagerPawn::AManagerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AManagerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AManagerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO: GameOver when there's no Units remained
}

void AManagerPawn::MoveManager()
{
	// Get the current viewport
	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();

	if (ViewportClient)
	{
		// Get the screen size
		FVector2D ScreenSize;
		ViewportClient->GetViewportSize(ScreenSize);

		// Get the current cursor position
		FVector2D MousePosition;
		ViewportClient->GetMousePosition(MousePosition);

		// Check if the cursor is near the left edge
		if (MousePosition.X <= ScreenEdgeThreshold)
		{
			// Move the camera to the left
			FVector NewCameraPosition = Camera->GetComponentLocation() - Camera->GetRightVector() * CameraMovementSpeed;
			Camera->SetWorldLocation(NewCameraPosition);
		}
		// Check if the cursor is near the right edge
		else if (MousePosition.X >= ScreenSize.X - ScreenEdgeThreshold)
		{
			// Move the camera to the right
			FVector NewCameraPosition = Camera->GetComponentLocation() + Camera->GetRightVector() * CameraMovementSpeed;
			Camera->SetWorldLocation(NewCameraPosition);
		}

		// Check if the cursor is near the top edge
		if (MousePosition.Y <= ScreenEdgeThreshold)
		{
			// Move the camera upwards
			FVector NewCameraPosition = Camera->GetComponentLocation() + Camera->GetUpVector() * CameraMovementSpeed;
			Camera->SetWorldLocation(NewCameraPosition);
		}
		// Check if the cursor is near the bottom edge
		else if (MousePosition.Y >= ScreenSize.Y - ScreenEdgeThreshold)
		{
			// Move the camera downwards
			FVector NewCameraPosition = Camera->GetComponentLocation() - Camera->GetUpVector() * CameraMovementSpeed;
			Camera->SetWorldLocation(NewCameraPosition);
		}
	}
}

void AManagerPawn::ZoomManager(const FInputActionValue& Value)
{
	// Check if the input value is valid and if the camera is valid
	if (Value.Get<float>() != 0.0f && Camera)
	{
		// Calculate the amount of zoom based on the input value and zoom speed
		float ZoomAmount = Value.Get<float>() * CameraZoomSpeed;

		// Apply the zoom by updating the camera's distance from its target
		FVector NewCameraLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * ZoomAmount;

		// Set the new camera position
		Camera->SetWorldLocation(NewCameraLocation);
	}
}


void AManagerPawn::MoveUnits()
{
	FVector StartTrace;
	FVector EndTrace;

	// Get mouse position
	FVector2D MousePosition;
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y);
	}

	// Get raycast origin and direction from mouse
	FVector WorldLocation, WorldDirection;
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	}

	// Calculate end of raycast
	StartTrace = WorldLocation;
	EndTrace = StartTrace + WorldDirection * 10000.f; // Arbitrary length, you can adjust it according to your needs

	// Perform raycast to get destination
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams))
	{
		FVector Destination = HitResult.Location;

		// For each possessed unit
		for (auto Unit : PossessedUnits)
		{
			AAIController* UnitController = Cast<AAIController>(Unit->GetController());

			if (UnitController)
			{
				UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
				if (NavSystem)
				{
					if(Unit && Unit->CanMove) UnitController->MoveToLocation(Destination, AcceptanceRadius);
				}
			}
		}
	}
}

void AManagerPawn::Interact()
{
	SelectionClickMode ? SelectUnits() : SpawnActorAtLocation(ActorToSpawn);
}

void AManagerPawn::SelectUnits()
{
	FVector StartTrace;
	FVector EndTrace;

	// Get mouse position
	FVector2D MousePosition;
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y);
	}

	// Get raycast origin and direction from mouse
	FVector WorldLocation, WorldDirection;
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	}

	// Calculate end of raycast
	StartTrace = WorldLocation;
	EndTrace = StartTrace + WorldDirection * 10000.f; // Arbitrary length, you can adjust it according to your needs

	// Perform raycast to get destination
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = false;
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Pawn, CollisionParams))
	{
		// Check if the hit actor is an UnitCharacter
		AUnitCharacter* HitUnitCharacter = Cast<AUnitCharacter>(HitResult.GetActor());
		if (HitUnitCharacter)
		{
			AEnemyUnitCharacter* EnemyUnitCharacter = Cast<AEnemyUnitCharacter>(HitUnitCharacter);
			
			// Add the hit unit character to the PossessedUnits array if it's not already in it
			if (!PossessedUnits.Contains(HitUnitCharacter) && !EnemyUnitCharacter)
			{
				HitUnitCharacter->OnSelect();
				PossessedUnits.Add(HitUnitCharacter);
			}
		}
	}
}

void AManagerPawn::SpawnActorAtLocation(TSubclassOf<AActor> AcToSpawn)
{
	FVector StartTrace;
	FVector EndTrace;

	// Get mouse position
	FVector2D MousePosition;
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y);
	}

	// Get raycast origin and direction from mouse
	FVector WorldLocation, WorldDirection;
	if (GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	}
	
	// Calculate end of raycast
	StartTrace = WorldLocation;
	EndTrace = StartTrace + WorldDirection * 10000.f; // Arbitrary length, you can adjust it according to your needs

	// Perform raycast to get destination
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceSingleByProfile(HitResult, StartTrace, EndTrace, "BlockAll", CollisionParams))
	{
		FVector SpawnLocation = FVector(
			HitResult.ImpactPoint.X,
			HitResult.ImpactPoint.Y,
			HitResult.ImpactPoint.Z + 100);
		
		GetWorld()->SpawnActor<AActor>(AcToSpawn, SpawnLocation, FRotator::ZeroRotator);
		SelectionClickMode = true;
	}
}

void AManagerPawn::DeselectUnits()
{
	for (auto Unit : PossessedUnits)
	{
		if(Unit) Unit->OnDeselect();
	}
	PossessedUnits.Empty();
}


