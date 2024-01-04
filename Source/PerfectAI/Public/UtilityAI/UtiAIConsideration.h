// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

#include "UtiAIScoreData.h"

#include "UtiAIConsideration.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PERFECTAI_API UUtiAIConsideration : public UObject
{
	GENERATED_BODY()
	
public:

	FUtiAIScoreData GetScore();

private:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString TempInput;

	UPROPERTY()
	FString TempCurve;

	UPROPERTY()
	FString TempParams;
};
