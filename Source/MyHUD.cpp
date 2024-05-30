// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

void UMyHUD::SetCointCount()
{
	// Gets coin count from game instance and updates hud text to show correct coint count number
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CoinCountNumber = GI->GetCoinCount();
	FString CountStr = FString::FromInt(CoinCountNumber);
	FText CountTxt = FText::FromString(CountStr);
	CoinCount->SetText(CountTxt);
}
