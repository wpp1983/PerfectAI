// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/Consideration/PAI_Consideration_Distance.h"

#include "AIController.h"
#include "UtilityAI/PAIActionData.h"
#include "UtilityAI/PAIResponseCurve.h"

UPAI_Consideration_Distance::UPAI_Consideration_Distance(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	Minimum = 0;
	Maximum = 5000;
}

float UPAI_Consideration_Distance::Score(const FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const
{
	if (!Context.Target || !Context.AIController || !Context.AIController->GetPawn())
	{
		// return a result like if the target were at max distance
		return ResponseCurve->ComputeValue(Maximum);
	}
	
	const float Input = FVector::Distance(Context.AIController->GetPawn()->GetActorLocation(), Context.Target->GetActorLocation());
	const float Normalized = (Input - Minimum) / (Maximum - Minimum);

	return ResponseCurve->ComputeValue(Normalized);
}
