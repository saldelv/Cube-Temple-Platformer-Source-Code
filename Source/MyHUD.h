// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class THISGAME_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Function to update coin count shown
	void SetCointCount();

	// Text shown on screen
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CoinText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CoinCount;

	// Coin number to change to convert to text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	int CoinCountNumber = 0;

};
