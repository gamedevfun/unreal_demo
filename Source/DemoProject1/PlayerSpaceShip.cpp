// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "DemoProject1GameModeBase.h"
#include "GameFramework/FloatingPawnMovement.h"

APlayerSpaceship::APlayerSpaceship()
{
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("SpaceMovement");
	Movement->SetUpdatedComponent(RootComponent);

	Tags.Add(FName(TEXT("PLAYER")));
}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();

	auto fieldSize = GameMode->GetFieldSize();
	SetActorLocation(FVector(fieldSize.X * 0.5f, fieldSize.Y, 0.0f));
	SetActorRotation(FRotator::MakeFromEuler(FVector::ZeroVector));
}


// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerSpaceship::MoveRight);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APlayerSpaceship::TryShoot);
}

void APlayerSpaceship::MoveRight(float Value)
{
	auto location = GetActorLocation();
	if (location.X < 0 && Value < 0.0f)
	{
		location.X = 0.0f;
		SetActorLocation(location);
		Restart();
		return;
	}

	if (location.X >= GameMode->GetFieldSize().X && Value > 0.0f)
	{
		location.X = GameMode->GetFieldSize().X;
		Restart();
		SetActorLocation(location);
		return;
	}

	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

float APlayerSpaceship::GetShootDelay()
{ 
	return GameMode->GetPlayerShootDelay();
}

UPawnMovementComponent* APlayerSpaceship::GetMovementComponent() const
{
	return Movement;
}