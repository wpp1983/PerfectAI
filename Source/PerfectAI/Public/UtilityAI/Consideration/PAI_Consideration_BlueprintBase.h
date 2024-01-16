// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UtilityAI\BTService_PAI_Consideration.h"
#include "PAI_Consideration_BlueprintBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PERFECTAI_API UPAI_Consideration_BlueprintBase : public UBTService_PAI_Consideration
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	float DoScore(const struct FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const;
	
public:
	virtual float Score(const struct FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
	virtual bool UsesBlueprint() const override;
#endif
};
