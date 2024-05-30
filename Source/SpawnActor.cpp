// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creates components
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;

}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();

	// Start spawning if enabled
	if (ShouldSpawn) {
		ScheduleActorSpawn();
	}
	
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

bool ASpawnActor::Spawn() {
	bool SpawnedActor = false;
	if (ActorClassToBeSpawned) {
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		// Get random location in box to spawn
		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();

		// Spawn
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
	}
	return SpawnedActor;
}

void ASpawnActor::EnableActorSpawning(bool Enable) {
	// Change if this should spawn anything
	ShouldSpawn = Enable;

	// Start spawning if true
	if (Enable) {
		ScheduleActorSpawn();
	}
	// Stop spawning if false
	else {
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void ASpawnActor::ScheduleActorSpawn() {
	// Get random time to next spawn
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	// Set a timer for next spawn
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnActor::SpawnActorScheduled, DeltaToNextSpawn, false);
}

void ASpawnActor::SpawnActorScheduled() {
	// Create next spawn
	Spawn();
	// Schedule next spawn
	if (ShouldSpawn) {
		ScheduleActorSpawn();
	}
}
