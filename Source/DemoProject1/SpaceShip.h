// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"


UCLASS()
class DEMOPROJECT1_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceship();

	FVector GetSize() const;

	void BindOnDestroyed(std::function<void()> function);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void TryShoot();
	// override this for proper direction from different type of ships
	virtual float GetShootMoveDirection() { return 0.0f; }
	// override this for proper shoot delay
	virtual float GetShootDelay() { return 1.0f; }

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "View")
	UStaticMeshComponent* Mesh;

	float LastShootTime = 0.0f;
	class ADemoProject1GameModeBase* GameMode = nullptr;

private:
	std::function<void()> _onDestroyed;
};
