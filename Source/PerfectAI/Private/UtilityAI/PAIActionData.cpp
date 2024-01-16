#include "UtilityAI/PAIActionData.h"

#include "AIController.h"
#include "UtilityAI/PAICommon.h"

#include "..\..\Public\UtilityAI\BTService_PAI_Consideration.h"

DECLARE_CYCLE_STAT(TEXT("PAI Utility Action Select"),STAT_PAI_ActionSelect,STATGROUP_PAI);

void PAIActionSelector::AddAction(const FPAIActionData& InActionData, const FString& Name)
{
	const int32 Index = ActionsData.Add(InActionData);
   	ActionNameIndexMap.Add(Name, Index);
}

FPAIActionSelectorContext PAIActionSelector::ChooseBehavior(AAIController* Controller, UBehaviorTreeComponent* BtComp,
	const TArray<AActor*>& Targets)
{
	SCOPE_CYCLE_COUNTER(STAT_PAI_ActionSelect);

	if (Targets.IsEmpty())
	{
		return {};
	}

	FPAIActionSelectorContext BestContext;

	for (int32 Idx = 0; Idx < ActionsData.Num(); Idx++)
	{
		for (AActor* Target : Targets)
		{
			if (ActionsData[Idx].Considerations.IsEmpty())
			{
				continue;
			}


			FPAIActionSelectorContext Context;
			Context.Selector= this;
			Context.ActionIndex = Idx;
			Context.AIController = Controller;
			Context.Target = Target;
			Context.TotalScore = ActionsData[Idx].InitialWeight;

			for (const auto& Consideration : ActionsData[Idx].Considerations)
			{
				const float Score = Consideration->ComputeScore(Context, BtComp);
				if (Score <= 0)
				{
					Context.TotalScore = 0;
					break;
				}

				const float Modification = (1.0 - Score) * ActionsData[Idx].CompensationFactor;
				Context.TotalScore *= Score + (Modification * Score);
			}

			if (Context.TotalScore == 1)
			{
				return Context;
			}

			if (Context.TotalScore > BestContext.TotalScore)
			{
				BestContext = Context;
			}
		}
	}

	return BestContext;
}
