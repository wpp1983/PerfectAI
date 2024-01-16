// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\BTService_PAI_Consideration.h"
#include "PAI_Consideration_Distance.generated.h"

/**
 * 
 */
UCLASS()
class PERFECTAI_API UPAI_Consideration_Distance : public UBTService_PAI_Consideration
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Utility|Range")
	float Minimum;

	UPROPERTY(EditAnywhere, Category = "Utility|Range")
	float Maximum;

	virtual float Score(const FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const override;
};
