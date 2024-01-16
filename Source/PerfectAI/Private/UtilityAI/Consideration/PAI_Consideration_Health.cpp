// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/Consideration/PAI_Consideration_Health.h"

#include "AIController.h"
#include "UtilityAI/PAIActionData.h"
#include "UtilityAI/PAIResponseCurve.h"


UPAI_Consideration_Health::UPAI_Consideration_Health(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	TargetsSelf = true;
}

float UPAI_Consideration_Health::Score(const FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const
{
	AActor* Target = Context.Target;

	if (TargetsSelf && Context.AIController)
	{
		Target = Context.AIController->GetPawn();
	}



	return ResponseCurve->ComputeValue(0.5 / 1);
}
