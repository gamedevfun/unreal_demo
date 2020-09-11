// Copyright Epic Games, Inc. All Rights Reserved.


#include "DemoProject1GameModeBase.h"
#include "Bullet.h"
#include "EnemySpaceship.h"
#include "GameFramework/GameUserSettings.h"

ABullet* ADemoProject1GameModeBase::SpawnBullet(const FVector& Location, const FName& IgnoreKillActorTag)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = nullptr;
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save bullet into a map
	auto bullet = GetWorld()->SpawnActor<ABullet>(BulletClass.Get(), Location, FRotator::ZeroRotator, SpawnInfo);
	if(bullet)
		bullet->SetKillIgnoreActorTag(IgnoreKillActorTag);
	return bullet;
}


AEnemySpaceship* ADemoProject1GameModeBase::SpawnEnemy(const FVector& Location)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = nullptr;
	SpawnInfo.bNoFail = true;
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save enemies into a map
	auto enemyShip = GetWorld()->SpawnActor<AEnemySpaceship>(EnemySpaceshipClass.Get(), Location, FRotator::ZeroRotator, SpawnInfo);
	return enemyShip;
}

void ADemoProject1GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	_enemyWaves.Init(this);
	_enemyWaves.FirstWave();
}
