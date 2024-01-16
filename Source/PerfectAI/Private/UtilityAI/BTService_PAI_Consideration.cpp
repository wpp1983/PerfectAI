// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\UtilityAI\BTService_PAI_Consideration.h"

UBTService_PAI_Consideration::UBTService_PAI_Consideration(const FObjectInitializer& ObjectInitializer)
{

	NodeName = "Consideration";
	
	bNotifyCeaseRelevant = false;
	bNotifyBecomeRelevant = false;
	bNotifyTick = false;
	
	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

float UBTService_PAI_Consideration::ComputeScore(const FPAIActionSelectorContext& Context,
	UBehaviorTreeComponent* BtComp) const
{
	float ScoreResult = Score(Context, BtComp);
	if (bInverseScore)
	{
		ScoreResult = 1.0f - ScoreResult;
	}

	return ScoreResult;
}

float UBTService_PAI_Consideration::Score(const FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const
{
	return 0.0f;
}
