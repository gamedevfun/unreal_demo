// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyWaves.h"
#include "DemoProject1GameModeBase.generated.h"

class ABullet;
class AEnemySpaceship;

/**
 * 
 */
UCLASS()
class DEMOPROJECT1_API ADemoProject1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	FIntVector GetFieldSize() const { return FieldSize; }

	ABullet* SpawnBullet(const FVector& Location, const FName& IgnoreKillActorTag);

	AEnemySpaceship* SpawnEnemy(const FVector& Location);

	float GetPlayerShootDelay() const { return PlayerShootDelay;  }

	FVector2D GetEnemyShootDelayRange() const { return EnemyShootDelayRange; }

	int32 GetInitEnemyWaveCount() const { return InitEnemyWaveCount; }

	int32 GetEnemyWaveGrowBy() const { return EnemyWaveGrowBy; }

	void AddScore(int32 Value) { _score += Value; }

	int32 GetScore() const { return _score; }

	void NextWave() { _waveCount++; }

protected:

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UPROPERTY(EditAnywhere)
	FIntVector FieldSize;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float PlayerShootDelay = 0.4f;

	UPROPERTY(EditAnywhere)
	FVector2D EnemyShootDelayRange;

	UPROPERTY(EditAnywhere)
	int32 InitEnemyWaveCount = 8;

	UPROPERTY(EditAnywhere)
	int32 EnemyWaveGrowBy = 4;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<AEnemySpaceship> EnemySpaceshipClass;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Values)
	int32 _score = 0;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Values)
	int32 _waveCount = 0;

private:

	EnemyWaves _enemyWaves;
};
