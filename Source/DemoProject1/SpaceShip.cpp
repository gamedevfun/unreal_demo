// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "DemoProject1GameModeBase.h"
#include "Bullet.h"

// Sets default values
ASpaceship::ASpaceship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

FVector ASpaceship::GetSize() const
{
	return Mesh->Bounds.GetBox().GetSize();
}

void ASpaceship::BindOnDestroyed(std::function<void()> function)
{
	_onDestroyed = std::move(function);
}

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();

	auto gameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<ADemoProject1GameModeBase>(gameMode);
}

void ASpaceship::TryShoot()
{
	auto time = GetWorld()->GetTimeSeconds();
	auto delay = GetShootDelay();
	if (time - LastShootTime < delay)
		return;

	auto location = GetActorLocation();
	location.Y += GetSize().Y * 0.5f * FMath::Sign(GetShootMoveDirection());
	auto ignoreActorTag = Tags.Num() == 0 ? FName() : Tags[0];
	auto bullet = GameMode->SpawnBullet(location, ignoreActorTag);
	if (bullet == nullptr)
		return;

	auto modeDirection = GetShootMoveDirection();
	bullet->SetMoveDirection(modeDirection);

	LastShootTime = time;
}

void ASpaceship::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason != EEndPlayReason::Type::Destroyed)
		return;
		
	if (_onDestroyed)
		_onDestroyed();
}
