// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBossHUD.h"

// Decreases bosses health bar by a third for each hit
void UMyBossHUD::UpdateHealth()
{
	HealthPercent -= 0.34;
	if (HealthPercent < 0) {
		HealthPercent = 0;
	}
	HealthBar->SetPercent(HealthPercent);
}

// Returns current boss health
float UMyBossHUD::GetHealth()
{
	return HealthPercent;
}
