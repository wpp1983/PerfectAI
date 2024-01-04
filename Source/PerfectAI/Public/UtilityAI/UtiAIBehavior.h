// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "UtiAIScoreData.h"

#include "UtiAIBehavior.generated.h"

class UUtiAIComponent;
class UUtiAIConsideration;
class UUtiAITask;
/**
 * 
 */
UCLASS(Blueprintable)
class PERFECTAI_API UUtiAIBehavior : public UObject
{
	GENERATED_BODY()

public:
	// UFUNCTION()
	FUtiAIScoreData GetUtilityScore();

	void Start(UUtiAIComponent& OwnerComp);

	void Tick(float DeltaTime);

	bool IsFinish() const;

	FString GetDescription() const;

private:
	UPROPERTY()
	TArray<TObjectPtr<UUtiAIConsideration>> Considerations;

	UPROPERTY()
	TObjectPtr<UUtiAITask> Task;
};