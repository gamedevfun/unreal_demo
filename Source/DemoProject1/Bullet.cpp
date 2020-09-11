// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "DemoProject1GameModeBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ABullet::SetMoveDirection(float MoveDirection)
{
	_moveDirection = MoveDirection;
	float angle = MoveDirection > 0.0f ? 90.0f : 270.0f;
	SetActorRotation(FRotator::MakeFromEuler(FVector(angle, 0.0f, 0.0f)));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	auto gameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<ADemoProject1GameModeBase>(gameMode);

	// for some unknown reason this code not working properly if it placed in constructor, but unreal docs show example 
	// with code in constructor see https://docs.unrealengine.com/en-US/Gameplay/ClassCreation/CodeOnly/index.html
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);       // set up a notification for when this component overlaps something
	Mesh->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);       // set up a notification for when this component overlaps something
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto location = GetActorLocation();
	auto size = Mesh->Bounds.GetBox().GetSize();

	if (location.Y < -size.Y)
	{
		Destroy();
		return;
	}

	if (location.Y >= GameMode->GetFieldSize().Y + size.Y)
	{
		Destroy();
		return;
	}

	AddActorWorldOffset(FVector(0.0f, _moveDirection, 0.0f) * DeltaTime);
}

/** called when something enters the sphere component */
void ABullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// this weird but we can not pass parametr when spawn actor so overlap can called when bullet spawned and do not set ignore actor tag
	// so ignore this logic while tag is none, we assume that it none only on actor that spawn bullet
	if (_killIgnoreActorTag.IsNone())
		return;

	if (OtherActor->ActorHasTag(_killIgnoreActorTag))
		return;

	auto name = OtherActor->GetFName();

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Name is %s!"), *name.ToString()));
#endif

	UE_LOG(LogTemp, Log, TEXT("Destroy UObject named: %s"), *GetName());
	OtherActor->Destroy();
	Destroy();
}

/** called when something leaves the sphere component */
void ABullet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

