// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/BTComposite_PAI_Brain.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "UtilityAI/PAIActionData.h"
#include "..\..\Public\UtilityAI\BTService_PAI_Consideration.h"
#include "UtilityAI/BTTask_PAI_Action.h"

UBTComposite_PAI_Brain::UBTComposite_PAI_Brain(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = TEXT("PAI Brain");
}

void UBTComposite_PAI_Brain::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTMemoryInit::Type InitType) const
{
	if (InitType == EBTMemoryInit::Initialize)
	{
		PAIBTComposite_BrainMemory * Memory = CastInstanceNodeMemory<PAIBTComposite_BrainMemory>(NodeMemory);
		Memory->Context = {};
		TArray<UBTTask_PAI_Action*> AllActions;
		GetAllActions(AllActions);
		for (int32 Index = 0; Index < AllActions.Num(); ++Index)
		{
			const auto ChildAction = AllActions[Index];
			FPAIActionData  ActionData;
			ActionData.InitialWeight = ChildAction->InitialWeight;
			for (auto Service : ChildAction->Services)
			{
				if (UBTService_PAI_Consideration* Consideration = Cast<UBTService_PAI_Consideration>(Service))
				{
					ActionData.Considerations.Add(Consideration);
				}
			}
			ActionData.CompensationFactor = 1.0 - (1.0 / ActionData.Considerations.Num());

			Memory->ActionSelector.AddAction(ActionData, ChildAction->GetNodeName());
		}
	}
}

void UBTComposite_PAI_Brain::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBActorAsset = GetBlackboardAsset();
	if (ensure(BBActorAsset))
	{
		BlackboardTargetKey.ResolveSelectedKey(*BBActorAsset);
		BlackboardLKPKey.ResolveSelectedKey(*BBActorAsset);
	}
}

uint16 UBTComposite_PAI_Brain::GetInstanceMemorySize() const
{
	return sizeof(PAIBTComposite_BrainMemory);
}

void UBTComposite_PAI_Brain::GetAllActions(TArray<UBTTask_PAI_Action*>& OutAllActions) const
{
	OutAllActions.Empty();
	for (int32 Idx = 0; Idx < GetChildrenNum(); ++Idx)
	{
		auto ChildAction = Cast<UBTTask_PAI_Action>(Children[Idx].ChildTask);
		if (ChildAction == nullptr)
		{
			continue;
		}

		OutAllActions.Add(ChildAction);
	}	
}

UBTTask_PAI_Action* UBTComposite_PAI_Brain::GetAction(int32 Index) const
{
	return Children.IsValidIndex(Index) ? Cast<UBTTask_PAI_Action>(Children[Index].ChildTask) : nullptr;
}

int32 UBTComposite_PAI_Brain::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild,
                                                  EBTNodeResult::Type LastResult) const
{
	PAIBTComposite_BrainMemory* Memory = GetNodeMemory<PAIBTComposite_BrainMemory>(SearchData);
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;
	AActor* Target = nullptr;
	const int32 CurrentActionIndex = Memory->Context.ActionIndex;
	const auto* CurrentAction =GetAction(CurrentActionIndex);
	// Reasons why the current behavior may not be valid for execution:
	// - It's the same as the previous and it's non-interruptible.
	// - It's the same as the previous behavior and it already failed to execute.
	// - Its score is not above 0.
	const bool bSameAsPrevious = PrevChild == CurrentActionIndex;
	if (!(bSameAsPrevious && CurrentAction && !CurrentAction->bInterruptible) &&
		!(bSameAsPrevious && LastResult == EBTNodeResult::Failed) && (Memory->Context.TotalScore > 0.f))
	{
		NextChildIdx = Memory->Context.ActionIndex;
	}

	Target = Memory->Context.Target;

	SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardTargetKey.SelectedKeyName, Target);
	if (Target)
	{
		SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardLKPKey.SelectedKeyName, Target->GetActorLocation());
	}

	return NextChildIdx;
}
