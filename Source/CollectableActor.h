// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

#include "CollectableActor.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJumpTriggerSignature, AActor*, OtherActor, UPrimitiveComponent*, OtherComp);

UCLASS()
class THISGAME_API ACollectableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableActor();

	UFUNCTION(BlueprintCallable)
	void Jump(float velocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Calls on overlap
	UFUNCTION()
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Time object lives after being collected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Livetime = 0.1f;

	// Speed of jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity = 3.f;

	// Speed of rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 5.f;

	// Actor that is allowed to collect this
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* TriggerClass = ADefaultPawn::StaticClass();

	// Sound to play when collected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CollectSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Static mesh and collision box
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintAssignable)
	FOnJumpTriggerSignature OnJumpTrigger;

	// Check if livetime should be decremented
	bool IsLaunched = false;
};
