// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/Tasks/UUtiAITask_RunBehaviorTree.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UtilityAI/UtiAIComponent.h"

UUUtiAITask_RunBehaviorTree::UUUtiAITask_RunBehaviorTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EUtiAITaskResult UUUtiAITask_RunBehaviorTree::ExecuteTask(UUtiAIComponent& OwnerComp)
{
	UE_CVLOG(BehaviorAsset == nullptr, OwnerComp.GetAIOwner(), LogUtiAI, Error, TEXT("\'%s\' is missing BehaviorAsset!"), *GetName());
	if (BehaviorAsset == nullptr)
	{
		return EUtiAITaskResult::Failed;
	}
	
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	UBehaviorTreeComponent* BTComp = AIOwner->GetComponentByClass<UBehaviorTreeComponent>();
	if (BTComp == nullptr)
	{
		BTComp = NewObject<UBehaviorTreeComponent>(this, TEXT("BTComponent"));
		BTComp->RegisterComponent();
		REDIRECT_OBJECT_TO_VLOG(BTComp, AIOwner);
	}

	check(BTComp != NULL);
	BTComp->StartTree(*BehaviorAsset, EBTExecutionMode::SingleRun);
	if (BTComp->IsRunning())
	{
		return EUtiAITaskResult::InProgress;
	}
	else if (BTComp->TreeHasBeenStarted())
	{
		return EUtiAITaskResult::Succeeded;
	}
	else
	{
		return EUtiAITaskResult::Failed;
	}
	

}

EUtiAITaskResult UUUtiAITask_RunBehaviorTree::AbortTask(UUtiAIComponent& OwnerComp)
{
	return Super::AbortTask(OwnerComp);
}

void UUUtiAITask_RunBehaviorTree::TickTask(UUtiAIComponent& OwnerComp, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, DeltaSeconds);
}

void UUUtiAITask_RunBehaviorTree::OnMessage(UUtiAIComponent& OwnerComp, FName Message, int32 RequestID, bool bSuccess)
{
	Super::OnMessage(OwnerComp, Message, RequestID, bSuccess);
}

void UUUtiAITask_RunBehaviorTree::OnTaskFinished(UUtiAIComponent& OwnerComp, EUtiAITaskResult TaskResult)
{
	Super::OnTaskFinished(OwnerComp, TaskResult);
}
