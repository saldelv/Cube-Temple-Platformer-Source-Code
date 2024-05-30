// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSceneComponent.h"

// Sets default values for this component's properties
UMoveSceneComponent::UMoveSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Assign value to set if move should be available
void UMoveSceneComponent::EnableMovement(bool ShouldMove) {
	MoveEnable = ShouldMove;
	SetComponentTickEnabled(MoveEnable);
}

// Clear distance and set to origin
void UMoveSceneComponent::ResetMovement() {
	CurrentDistance = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}

// Change move direction
void UMoveSceneComponent::SetMoveDirection(int Direction) {
	MoveDirection = Direction >= 1 ? 1 : -1;
}

// Called when the game starts
void UMoveSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set start location
	StartRelativeLocation = GetRelativeLocation();

	// Compute normalized movement
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();

	// Compute maximum movement
	MaxDistance = MoveOffset.Length();

	// Check if ticking is required
	SetComponentTickEnabled(MoveEnable);
		
}


// Called every frame
void UMoveSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Set current distance
	if (MoveEnable) {
		CurrentDistance += DeltaTime * Speed * MoveDirection;
		if (CurrentDistance >= MaxDistance || CurrentDistance <= 0.0f) {
			
			// Invert direction
			MoveDirection *= -1;

			// Fire event
			OnEndpointReached.Broadcast(CurrentDistance >= MaxDistance);

			// Clamp distance
			CurrentDistance = FMath::Clamp(CurrentDistance, 0.0f, MaxDistance);
		}
	}

	// Compute and set current location
	SetRelativeLocation(StartRelativeLocation + MoveOffsetNorm * CurrentDistance);
}

