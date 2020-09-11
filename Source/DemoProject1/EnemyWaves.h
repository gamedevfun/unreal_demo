#pragma once

#include "CoreMinimal.h"

class ADemoProject1GameModeBase;

/**
 * 
 */
class EnemyWaves
{
public:

	void Init(ADemoProject1GameModeBase* GameMode);
	void FirstWave();

private:

	void OnEnemyDestroyed();
	void SpawnNext(int32 Count);
	class AEnemySpaceship* SpawnOneEnemy(const FVector& position);

	int32 _enemiesInCurrentWaveCount = 0;
	int32 _enemiesInCurrentWave = 0;
	ADemoProject1GameModeBase* _gameMode;
};
