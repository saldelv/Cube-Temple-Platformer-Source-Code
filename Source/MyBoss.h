// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "MyBossHUD.h"
#include "MyProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyGameInstance.h"

#include "MyBoss.generated.h"

UCLASS()
class THISGAME_API AMyBoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Projectile that the boss spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

private:
	// Boss static mesh and collision box
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	// Sound that plays when the boss is hit
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* HitSound;

	//Boss Hud for health bar
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyBossHUD> BossHudClass;

	UPROPERTY()
	class UMyBossHUD* BossHud;

	// Name of level to load after boss is defeated
	UPROPERTY(EditAnywhere)
	FName LevelToLoad;

	// Values for attack speed, height, and direction
	UPROPERTY(EditAnywhere)
	float AttackTimeOffset = 2.f;
	float AttackTime = 0.f;

	float Direction = 1.f;

	UPROPERTY(EditAnywhere)
	float AttackHeightOffset = 150.f;
	float AttackHeight = 0.f;

	// Values for launching player back after boss is hit
	UPROPERTY(EditAnywhere)
	float HitTimeDefault = 4.f;

	UPROPERTY(EditAnywhere)
	float HitDistance = 2100.f;

	bool Hit = false;
	float HitTime = 0.f;

};
