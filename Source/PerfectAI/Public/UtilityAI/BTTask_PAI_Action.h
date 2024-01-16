// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_RunBehaviorDynamic.h"
#include "BTTask_PAI_Action.generated.h"

struct FPAI_ActionMemory 
{
	bool bExecuting = false;
};

/**
 * 
 */
UCLASS()
class PERFECTAI_API UBTTask_PAI_Action : public UBTTask_RunBehaviorDynamic
{
	GENERATED_UCLASS_BODY()


	UPROPERTY(EditAnywhere, Category = "Utility")
	bool bInterruptible = true;

	UPROPERTY(EditAnywhere, Category = "Utility",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float InitialWeight = 1.0;

#if WITH_EDITOR
	FString GetStaticDescription() const override;
#endif

protected:

	virtual uint16 GetInstanceMemorySize() const override;
};
