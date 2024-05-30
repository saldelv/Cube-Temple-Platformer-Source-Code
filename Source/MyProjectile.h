// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/StaticMesh.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "MyProjectile.generated.h"

UCLASS()
class THISGAME_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Projectile components
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	// Time projectile lasts for
	UPROPERTY(EditAnywhere)
	float LiveTime = 1.f;
};
