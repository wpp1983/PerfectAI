// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PAIActionData.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_PAI_Brain.generated.h"

struct PAIBTComposite_BrainMemory : public FBTCompositeMemory
{
	PAIActionSelector ActionSelector;
	FPAIActionSelectorContext Context;
	float LastActionChangeTime;
	TArray<struct FPAI_ActionMemory*> ActionMemories;
};

/**
 * 
 */
UCLASS()
class PERFECTAI_API UBTComposite_PAI_Brain : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()


	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override final;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual uint16 GetInstanceMemorySize() const override;

	void GetAllActions(TArray<class UBTTask_PAI_Action*>& OutAllActions) const;
	UBTTask_PAI_Action* GetAction(int32 Index) const;	

protected:
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;

	/* Blackboard key where the target is stored */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardTargetKey;

	/* Blackboard key where the last known position of the target is stored */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardLKPKey;
};
