// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityAIToolsHelper.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class PERFECTAI_API UUtilityAIToolsHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "PAI Tools")
	static FString ExportUtilityAIToJson(UBehaviorTree* BehaviorTree);
};
