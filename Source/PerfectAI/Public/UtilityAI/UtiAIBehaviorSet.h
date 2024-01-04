// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtiAIBehaviorSet.generated.h"

class UUtiAIBehavior;
class UBlackboardData;
/**
 * 
 */
UCLASS()
class PERFECTAI_API UUtiAIBehaviorSet : public UObject
{
	GENERATED_BODY()

public:
	TArray<TObjectPtr<UUtiAIBehavior>> Behaviors;

	/** blackboard asset for this tree */
	UPROPERTY()
	TObjectPtr<UBlackboardData> BlackboardAsset;
};
