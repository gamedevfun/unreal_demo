#include "EnemyWaves.h"
#include "DemoProject1GameModeBase.h"
#include "EnemySpaceShip.h"
#include "GameFramework/Actor.h"


void EnemyWaves::Init(ADemoProject1GameModeBase* GameMode)
{
	_gameMode = GameMode;
	_enemiesInCurrentWaveCount = 8;
	_enemiesInCurrentWave = 8;
}

void EnemyWaves::FirstWave()
{
	SpawnNext(_enemiesInCurrentWaveCount);
}

void EnemyWaves::SpawnNext(int32 Count)
{
	auto fieldSize = _gameMode->GetFieldSize();
	auto spaceship = SpawnOneEnemy(FVector::ZeroVector);
	auto spaceshipSize = spaceship->GetSize();

	FVector position(0.0f);
	for (int32 i = 0; i < Count -1; ++i)
	{
		position.X += spaceshipSize.X * 2.0f;
		spaceship = SpawnOneEnemy(position);
	}

	_gameMode->NextWave();
}

AEnemySpaceship* EnemyWaves::SpawnOneEnemy(const FVector& position)
{
	AEnemySpaceship* spaceship = _gameMode->SpawnEnemy(position);
	spaceship->BindOnDestroyed([this]()
		{
			OnEnemyDestroyed();
		});
	return spaceship;
}

void EnemyWaves::OnEnemyDestroyed()
{
	_enemiesInCurrentWaveCount--;
	if (_enemiesInCurrentWaveCount == 0)
	{
		_enemiesInCurrentWaveCount = _enemiesInCurrentWave = _enemiesInCurrentWave + 4;
		SpawnNext(_enemiesInCurrentWaveCount);
	}
}
