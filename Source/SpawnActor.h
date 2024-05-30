// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "SpawnActor.generated.h"

UCLASS()
class THISGAME_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Functions used to spawn
	UFUNCTION(BlueprintCallable)
	bool Spawn();

	UFUNCTION(BlueprintCallable)
	void EnableActorSpawning(bool Enable);

private:
	UFUNCTION() // Needed to use timer
	void SpawnActorScheduled();

	void ScheduleActorSpawn();

public:
	// Class that is spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	// Editable spawn time variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 1.f;

private:
	// Spawn box component
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	// Sets if this spawns
	UPROPERTY(EditAnywhere)
	bool ShouldSpawn = true;

	// Timer for spawn timing
	FTimerHandle SpawnTimerHandle;
};
