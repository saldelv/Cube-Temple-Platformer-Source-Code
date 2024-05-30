// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

// Returns current coin count
float UMyGameInstance::GetCoinCount()
{
	return CoinCount;
}

// Returns current bow status
bool UMyGameInstance::GetHasBow()
{
	return HasBow;
}

// Returns current grapple status
bool UMyGameInstance::GetHasGrapple()
{
	return HasGrapple;
}

// Updates coin count
void UMyGameInstance::SetCoinCount(float c)
{
	CoinCount = c;
}

// Changes bow status
void UMyGameInstance::SetHasBow()
{
	if (HasBow == false) {
		HasBow = true;
	}
	else {
		HasBow = false;
	}
}

// Changes grapple status
void UMyGameInstance::SetHasGrapple()
{
	if (HasGrapple == false) {
		HasGrapple = true;
	}
	else {
		HasGrapple = false;
	}
}
