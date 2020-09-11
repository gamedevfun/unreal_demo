// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpaceship.h"
#include "DemoProject1GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AEnemySpaceship::AEnemySpaceship()
{
	Tags.Add(FName(TEXT("ENEMY")));
}

// Called when the game starts or when spawned
void AEnemySpaceship::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator::MakeFromEuler(FVector(90.0f, 0.0f, 0.0f)));

	auto shootDelayRange = GameMode->GetEnemyShootDelayRange();
	_shootDelay = FMath::RandRange(shootDelayRange.X, shootDelayRange.Y);
	_moveDirection = NewDirection();

	LastShootTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void AEnemySpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto location = GetActorLocation();
	if (location.X < 0)
	{
		_moveDirection = NewDirection(_moveDirection);
		location.X = 0.0f;
		location.Y += GetSize().Y;
		SetActorLocation(location);
	}
	else if (location.X > GameMode->GetFieldSize().X)
	{
		_moveDirection = NewDirection(_moveDirection);
		location.X = GameMode->GetFieldSize().X;
		location.Y += GetSize().Y;
		SetActorLocation(location);
	}

	if (location.Y > GameMode->GetFieldSize().Y)
	{
		auto player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (player && !player->IsActorBeingDestroyed())
		{
			player->Destroy();
		}
	}

	TryShoot();

	AddActorLocalOffset(FVector(1.0f, 0.0f, 0.0f) * _moveDirection * DeltaTime);
}

float AEnemySpaceship::NewDirection(float currentDirection)
{
	return GetSize().X * 3.0f * (currentDirection < 0.0f ? 1.0f : -1.0f);
}

void AEnemySpaceship::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GameMode)
		GameMode->AddScore(1);
}