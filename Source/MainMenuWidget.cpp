// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Add functions to be called when each button is clicked
	PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClickPlay);
	ControlsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClickControls);
	ExitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClickExit);
	BackButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClickBack);

}

void UMainMenuWidget::OnClickPlay()
{
	if (LevelToLoad != "") {
		// Changes input mode to allow keyboard input for playing
		UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = false;
		UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeGameOnly());

		// Loads first level
		FLatentActionInfo LatentInfo;
		UGameplayStatics::OpenLevel(this, LevelToLoad);
	}
}

void UMainMenuWidget::OnClickControls()
{
	// Switches main menu ui to show controls
	MenuSwitcher->SetActiveWidgetIndex(1);
}

void UMainMenuWidget::OnClickExit()
{
	// Ends the game instance
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Type::Quit, false);
}

void UMainMenuWidget::OnClickBack()
{
	// Switches main menu ui to show the original screen
	MenuSwitcher->SetActiveWidgetIndex(0);
}
