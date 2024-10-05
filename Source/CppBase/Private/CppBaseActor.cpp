// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"
#include "String"
#include "TimerManager.h"
#include "CppHubActor.h"

int num_object = 1 ;
int EnemyNum = 20;
bool isAlive = true;


// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(TimerHandle, this, &ACppBaseActor::OnTimeToSpawn, TimerRate, true)

	//ShowActorInformation();
}

void ACppHubActor::OnTimeToSpawn() {
  if (++CurrentTimerCount <= CurrentTimerCount)
	{
		const FVector Location = GetActorLocation() + FVector(FMath::FRandRange(200.0f, 1000.0f), FMath::FRandRange(200.0f, 1000.0f), 0.0f);
		const FRotator Rotation = FRotator::ZeroRotator;
		ACppBaseActor* SpawnObject = GetWorld()->SpawnActor<ACppBaseActor>(CppClass, Location, Rotation);
		if (SpawnObject)
		{
			SpawnedObjects.Add(SpawnObject);
		}

	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
          for (int i = CurrentTimerCount; i >= 1; --i) 
		{
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ACppHubActor::OnTimeToDestroy, DestroyTimerRate, true);
		}

	}

}

void ACppHubActor::OnTimeToDestroy()
{
	if (SpawnedObjects.IsEmpty()) {

		SpawnedObjects.Top()->Destroy();
		SpawnedObjects.Pop();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}
}

void ACppBaseActor::ShowActorInformation() {
	UE_LOG(LogTemp, Display, TEXT("A_CppBase_C_%i"), num_object);
	UE_LOG(LogTemp, Display, TEXT("Enemy Num: %d"), EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("is Alive: %i"), isAlive);
	num_object++;
	EnemyNum += 10;
	isAlive = !isAlive;
}

void ACppBaseActor::SinMovement() {



}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

