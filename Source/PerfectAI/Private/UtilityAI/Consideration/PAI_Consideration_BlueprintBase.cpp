// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/Consideration/PAI_Consideration_BlueprintBase.h"

float UPAI_Consideration_BlueprintBase::Score(const FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const
{
	return DoScore(Context, BtComp);
}

#if WITH_EDITOR

FName UPAI_Consideration_BlueprintBase::GetNodeIconName() const
{
	return Super::GetNodeIconName();
}

bool UPAI_Consideration_BlueprintBase::UsesBlueprint() const
{
	return true;
}

#endif
