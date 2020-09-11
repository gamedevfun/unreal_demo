
#pragma once

#include "CoreMinimal.h"
#include "Spaceship.h"
#include "EnemySpaceship.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT1_API AEnemySpaceship : public ASpaceship
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemySpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	float GetShootMoveDirection() override { return 200.0f; }

	float GetShootDelay() override { return _shootDelay; }

private:

	float _moveDirection = 10.5f;
	float _changeDirectionTime = 0.5f;
	float _shootDelay = 0.5f;

	float NewDirection(float currentDirection = -1.0f);
};
