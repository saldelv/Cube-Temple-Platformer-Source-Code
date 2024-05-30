// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"

#include "MyBossHUD.generated.h"

/**
 * 
 */
UCLASS()
class THISGAME_API UMyBossHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Functions to set and get boss health
	UFUNCTION(BlueprintCallable)
	void UpdateHealth();

	UFUNCTION(BlueprintCallable)
	float GetHealth();

	// Health bar components to edit
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealthBar;

	// Boss health percent
	UPROPERTY(EditAnywhere)
	float HealthPercent = 1.f;
};
