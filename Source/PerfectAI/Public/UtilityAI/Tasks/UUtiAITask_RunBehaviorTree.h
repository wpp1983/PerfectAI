// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UtilityAI/UtiAITask.h"
#include "UUtiAITask_RunBehaviorTree.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class PERFECTAI_API UUUtiAITask_RunBehaviorTree : public UUtiAITask
{
	GENERATED_UCLASS_BODY()
	
	virtual EUtiAITaskResult ExecuteTask(UUtiAIComponent& OwnerComp) override;

protected:
	virtual EUtiAITaskResult AbortTask(UUtiAIComponent& OwnerComp) override;
	virtual void TickTask(UUtiAIComponent& OwnerComp, float DeltaSeconds) override;
	virtual void OnMessage(UUtiAIComponent& OwnerComp, FName Message, int32 RequestID, bool bSuccess) override;
	virtual void OnTaskFinished(UUtiAIComponent& OwnerComp, EUtiAITaskResult TaskResult) override;

	/** behavior to run */
	UPROPERTY(Category = Node, EditAnywhere)
	TSoftObjectPtr<UBehaviorTree> BehaviorAsset;
};
