// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/UtiAITask.h"

UUtiAITask::UUtiAITask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}  

EUtiAITaskResult UUtiAITask::ExecuteTask(UUtiAIComponent& OwnerComp)
{
	return EUtiAITaskResult::Succeeded;
}

EUtiAITaskResult UUtiAITask::AbortTask(UUtiAIComponent& OwnerComp) 
{
	return EUtiAITaskResult::Succeeded;
}

void UUtiAITask::TickTask(UUtiAIComponent& OwnerComp, float DeltaSeconds)
{
}

void UUtiAITask::OnMessage(UUtiAIComponent& OwnerComp, FName Message, int32 RequestID, bool bSuccess)
{
}

void UUtiAITask::OnTaskFinished(UUtiAIComponent& OwnerComp, EUtiAITaskResult TaskResult)
{
}

void UUtiAITask::FinishLatentTask(UUtiAIComponent& OwnerComp, EUtiAITaskResult TaskResult)
{
}

void UUtiAITask::FinishLatentAbort(UUtiAIComponent& OwnerComp)
{
}
