// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

void AMyGameModeBase::InitGameState() {

	Super::InitGameState();

	// Sets default character to be my player character class
	if (DefaultPawnClass == ADefaultPawn::StaticClass() || !DefaultPawnClass) {
		DefaultPawnClass = CustomMyCharacterClass;
	}

}