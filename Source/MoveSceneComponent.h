// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveSceneComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveComponentReachEndpointSignature, bool, IsTopEndpoint);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THISGAME_API UMoveSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveSceneComponent();

	UFUNCTION(BlueprintCallable)
	void EnableMovement(bool ShouldMove);

	UFUNCTION(BlueprintCallable)
	void ResetMovement();

	UFUNCTION(BlueprintCallable)
	void SetMoveDirection(int Direction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Offset to move
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	// Move speed
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	// Enables movement
	UPROPERTY(EditAnywhere)
	bool MoveEnable = true;

	// On extreme reached event
	UPROPERTY(BlueprintAssignable)
	FOnMoveComponentReachEndpointSignature OnEndpointReached;

	// Computed locations
	FVector StartRelativeLocation;
	FVector MoveOffsetNorm;
	float MaxDistance = 0.0f;
	float CurrentDistance = 0.0f;
	int MoveDirection = 1;
};
