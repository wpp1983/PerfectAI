// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/BTService_PAI_Barin.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "UtilityAI/PAICommon.h"
#include "UtilityAI/BTComposite_PAI_Brain.h"
#include "UtilityAI/BTTask_PAI_Action.h"

DECLARE_CYCLE_STAT(TEXT("PAI Decorator Tick Node"), STAT_PAIDecoratorTickNode, STATGROUP_PAI);

UBTService_PAI_Barin::UBTService_PAI_Barin(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	NodeName = TEXT("PAI Brain Evaluator");
	bNotifyTick = true;
	SelectionCooldown = 0.25f;
}

void UBTService_PAI_Barin::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	SCOPE_CYCLE_COUNTER(STAT_PAIDecoratorTickNode);

	PAIBTService_BrainMemory* MyMemory = CastInstanceNodeMemory<PAIBTService_BrainMemory>(NodeMemory);
	if (!MyMemory || !MyMemory->BrainMemory)
	{
		return;
	}

	// Give the current behavior a moment to stabilize before we start looking for a new action
	if (MyMemory->BrainMemory->LastActionChangeTime + SelectionCooldown >= GetWorld()->GetTimeSeconds())
	{
		return;
	}

	const int32 CurrentActionIndex = MyMemory->BrainMemory->Context.ActionIndex;
	if (const UBTComposite_PAI_Brain* MyBrain = Cast<UBTComposite_PAI_Brain>(GetMyNode()))
	{
			if (const auto* CurrenAction = MyBrain->GetAction(CurrentActionIndex))
			{
				// If the current behavior is uninterruptible and it's executing, don't look for a new behavior
				if (!CurrenAction->bInterruptible && MyMemory->BrainMemory->ActionMemories[CurrentActionIndex]->bExecuting)
				{
					return;
				}
			}
	}

	EvaluateActions(&OwnerComp, MyMemory);
}

void UBTService_PAI_Barin::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTMemoryInit::Type InitType) const
{
	if (InitType == EBTMemoryInit::Initialize)
	{
		auto* MyMemory = CastInstanceNodeMemory<PAIBTService_BrainMemory>(NodeMemory);

		if (const auto* Brain = Cast<UBTComposite_PAI_Brain>(GetMyNode()))
		{
			// NOTE: const cast is okay because GetNodeMemory effectively does not touch the Node parameter.
			// It's an oversight that the Node parameter is not marged as const. Instead of fixing it in UE, the fix is here.
			MyMemory->BrainMemory = Brain->CastInstanceNodeMemory<PAIBTComposite_BrainMemory>(
				OwnerComp.GetNodeMemory(const_cast<UBTComposite_PAI_Brain*>(Brain), OwnerComp.GetActiveInstanceIdx()));
			if (MyMemory->BrainMemory)
			{
				MyMemory->BrainMemory->ActionMemories.Empty();

				TArray<UBTTask_PAI_Action*> AllActions;
				Brain->GetAllActions(AllActions);
				for (int32 Index = 0; Index <AllActions.Num(); Index++)
				{
						MyMemory->BrainMemory->ActionMemories.Add(
							AllActions[Index]->CastInstanceNodeMemory<FPAI_ActionMemory>(
								OwnerComp.GetNodeMemory(AllActions[Index], OwnerComp.GetActiveInstanceIdx())));
				}
			}
		}
	}
}



uint16 UBTService_PAI_Barin::GetInstanceMemorySize() const
{
	return sizeof(PAIBTService_BrainMemory);
}

void UBTService_PAI_Barin::EvaluateActions(UBehaviorTreeComponent* OwnerComp,
	PAIBTService_BrainMemory* MyMemory) const
{
	if (!MyMemory || !MyMemory->BrainMemory || !OwnerComp->GetAIOwner())
	{
		return;
	}

	auto* MyBrainMemory = MyMemory->BrainMemory;
	const AActor* PreviousActor = MyBrainMemory->Context.Target;

	UpdateActionContext(OwnerComp, MyBrainMemory);

	MyMemory->IsContextValid = MyBrainMemory->Context.TotalScore != 0;
	if (!MyMemory->IsContextValid)
	{
		return;
	}

	const int32 NextActionIndex = MyBrainMemory->Context.ActionIndex;
	MyBrainMemory->ActionSelector.ActionsData[NextActionIndex].LastExecutionTime = GetWorld()->GetTimeSeconds();

	// If the next Action is different from the previous or the target is different, stop the execution of the current Action
	if (NextActionIndex != static_cast<int32>(MyBrainMemory->CurrentChild) || PreviousActor != MyBrainMemory->Context.Target)
	{
		MyBrainMemory->LastActionChangeTime = GetWorld()->GetTimeSeconds();

		const int32 InstanceIdx = OwnerComp->FindInstanceContainingNode(GetParentNode());
		OwnerComp->RequestExecution(GetParentNode(), InstanceIdx, this, GetChildIndex(), EBTNodeResult::Succeeded);
	}
}

void UBTService_PAI_Barin::UpdateActionContext(UBehaviorTreeComponent* OwnerComp,
	PAIBTComposite_BrainMemory* MyBrainMemory) const
{
	if (AAIController* AIController = OwnerComp->GetAIOwner())
	{
		TArray<AActor*> Targets;
		AIController->GetPerceptionComponent()->GetKnownPerceivedActors(nullptr, Targets);
		Targets.Add(AIController->GetPawn());

		MyBrainMemory->Context = MyBrainMemory->ActionSelector.ChooseBehavior(AIController, OwnerComp, Targets);
	}
}
