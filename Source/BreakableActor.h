// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyProjectile.h"

#include "BreakableActor.generated.h"

UCLASS()
class THISGAME_API ABreakableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABreakableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Calls on overlap
	UFUNCTION()
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Time it exists before breaking
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Livetime = 0.1f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Static mesh and collision box
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	// Sound when breaks
	UPROPERTY(EditDefaultsOnly)
	USoundBase* BreakSound;
};
