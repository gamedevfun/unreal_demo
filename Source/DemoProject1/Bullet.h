// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class DEMOPROJECT1_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	void SetMoveDirection(float MoveDirection);

	void SetKillIgnoreActorTag(FName killIgnoreActorTag) { _killIgnoreActorTag = std::move(killIgnoreActorTag); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "View")
	UStaticMeshComponent* Mesh;

	/** called when something enters the sphere component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// it is both direction and speed(magnitude) like a vector but in one dimension 
	float _moveDirection = 1.0f;
	class ADemoProject1GameModeBase* GameMode = nullptr;
	FName _killIgnoreActorTag;
};
