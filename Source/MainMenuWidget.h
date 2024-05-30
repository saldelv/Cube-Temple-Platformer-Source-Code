// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WidgetSwitcher.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class THISGAME_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// Functions for buttons to call when clicked
	UFUNCTION()
	void OnClickPlay();
	void OnClickControls();
	void OnClickExit();
	void OnClickBack();


	// Buttons and text to add and edit
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ControlsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ControlsText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ExitText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* BackText;

	// Switches main ui
	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite)
	class UWidgetSwitcher* MenuSwitcher;


	// Name of the first level to load
	UPROPERTY(EditAnywhere)
	FName LevelToLoad;
};
