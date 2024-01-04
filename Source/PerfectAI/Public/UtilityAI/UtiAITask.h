// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UtiAI.h"
#include "UObject/Object.h"
#include "UtiAITask.generated.h"

class UUtiAIComponent;


/**
 */
UCLASS(Abstract)
class PERFECTAI_API UUtiAITask : public UObject
{
	GENERATED_UCLASS_BODY()

	/** starts this task, should return Succeeded, Failed or InProgress
	 *  (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EUtiAITaskResult ExecuteTask(UUtiAIComponent& OwnerComp);

protected:
	/** aborts this task, should return Aborted or InProgress
	 *  (use FinishLatentAbort() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EUtiAITaskResult AbortTask(UUtiAIComponent& OwnerComp);

public:
	/** helper function: finish latent executing */
	void FinishLatentTask(UUtiAIComponent& OwnerComp,EUtiAITaskResult TaskResult);

	/** helper function: finishes latent aborting */
	void FinishLatentAbort(UUtiAIComponent& OwnerComp);

protected:
	virtual void TickTask(UUtiAIComponent& OwnerComp, float DeltaSeconds);
	
	virtual void OnMessage(UUtiAIComponent& OwnerComp, FName Message, int32 RequestID, bool bSuccess);

	/** called when task execution is finished **/
	virtual void OnTaskFinished(UUtiAIComponent& OwnerComp, EUtiAITaskResult TaskResult);

};
