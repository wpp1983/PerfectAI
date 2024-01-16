// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PAI_Barin.generated.h"

struct PAIBTComposite_BrainMemory;

struct PAIBTService_BrainMemory
{
	bool IsContextValid = false;
	PAIBTComposite_BrainMemory* BrainMemory = nullptr;
};

/**
 * 
 */
UCLASS()
class PERFECTAI_API UBTService_PAI_Barin : public UBTService_BlackboardBase
{
	GENERATED_UCLASS_BODY()


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** Initializes the memories of all the nodes */
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;

	// virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual uint16 GetInstanceMemorySize() const override;

	// virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;

	// virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;

	void EvaluateActions(UBehaviorTreeComponent* OwnerComp, PAIBTService_BrainMemory* MyMemory) const;
	
	void UpdateActionContext(UBehaviorTreeComponent* OwnerComp, PAIBTComposite_BrainMemory* MyBrainMemory) const;

	/** How often a new behavior can be selected */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float SelectionCooldown;
};
