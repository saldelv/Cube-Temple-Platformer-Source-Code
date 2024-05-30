// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/DefaultPawn.h"
#include "MyCharacter.h"

#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THISGAME_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;

private:
	// Class of player character
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AMyCharacter> CustomMyCharacterClass = AMyCharacter::StaticClass();

};
