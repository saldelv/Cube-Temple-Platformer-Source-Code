// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THISGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Getter methods for game instance variables
	UFUNCTION()
	float GetCoinCount();

	UFUNCTION()
	bool GetHasBow();

	UFUNCTION()
	bool GetHasGrapple();

	// Setter methods for game instance variables
	UFUNCTION()
	void SetCoinCount(float c);

	UFUNCTION()
	void SetHasBow();

	UFUNCTION()
	void SetHasGrapple();
	
private:
	// Game instance variables
	UPROPERTY(EditAnywhere)
	float CoinCount = 0.f;

	UPROPERTY(EditAnywhere)
	bool HasBow = false;

	UPROPERTY(EditAnywhere)
	bool HasGrapple = false;
};
