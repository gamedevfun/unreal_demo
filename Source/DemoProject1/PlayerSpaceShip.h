// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spaceship.h"
#include "PlayerSpaceship.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT1_API APlayerSpaceship : public ASpaceship
{
	GENERATED_BODY()

public:

	APlayerSpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Value);

	float GetShootMoveDirection() override { return -250.0f; }

	float GetShootDelay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Movement)
	class UFloatingPawnMovement* Movement;
};
