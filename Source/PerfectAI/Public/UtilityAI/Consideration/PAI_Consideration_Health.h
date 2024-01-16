// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\BTService_PAI_Consideration.h"
#include "PAI_Consideration_Health.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTAI_API UPAI_Consideration_Health : public UBTService_PAI_Consideration
{
	GENERATED_UCLASS_BODY()

	virtual float Score(const FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const override;

	UPROPERTY(EditAnywhere, Category = "Utility")
	bool TargetsSelf;
};
