// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Engine/StaticMesh.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "CollectableActor.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "CableComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "MyCharacter.generated.h"

UCLASS()
class THISGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Controls functions
	void MoveFB(float Value);
	void MoveLR(float Value);
	void RotateLR(float Value);
	void RotateUD(float Value);

	void Jumps();
	void Dash();
	void Sprint();

	void Shoot();
	void Grapple();
	void EndGrapple();

public:
	// Classes for overlap actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CoinActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeHitBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BowActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> GrappleActorClass;

	// Player hud class
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyHUD> PlayerHudClass;

	UPROPERTY()
	class UMyHUD* PlayerHud;

	// Location for boss to teleport player to when hit
	UPROPERTY(EditAnywhere)
	FVector BossTeleport;

	// Sounds to play
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* GrappleSound;

	// Grapple values, public for blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector GrappleDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGrappling = false;

	bool Grappled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GrappleFinished = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrappleSpeed = 30.0f;

private:
	// Editable values for character
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float CameraLength = 200.0f;

	UPROPERTY(EditAnywhere)
	float InAirControl = 0.7f;

	UPROPERTY(EditAnywhere)
	float JumpHeight = 500.0f;

	UPROPERTY(EditAnywhere)
	float SecondJumpHeight = 200.0f;

	UPROPERTY(EditAnywhere)
	float BoostJumpDistance = 400.f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 450.0f;

	UPROPERTY(EditAnywhere)
	float DashDistance = 100.0f;

	UPROPERTY(EditAnywhere)
	float DashDistanceGround = 1150.0f;

	UPROPERTY(EditAnywhere)
	float DashHeight = 0.0f;

	UPROPERTY(EditAnywhere)
	float DashHeightGround = 0.12f;

	UPROPERTY(EditAnywhere)
	float DashTimeDefault = 0.1f;
	
	// Code only variables used in functions
	float DashTime;

	bool CanJump = true;
	bool CanSecondJump = false;

	FVector DashDirection;

	bool HasDashed = false;
	bool HasDashedGround = false;
	bool DashFinished = false;

	float WalkSpeed = 400.f;

	bool SprintHeld = false;

	bool BowPickedUp = false;
	bool GrapplePickedUp = false;

	// Player components
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BowMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* GrappleMesh;

	UPROPERTY(EditDefaultsOnly)
	UCableComponent* GrappleLine;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* PlayerCameraBoom;
};
