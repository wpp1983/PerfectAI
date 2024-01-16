// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PAI_Consideration.generated.h"

class UPAIResponseCurve;
/**
 * 
 */
UCLASS(Blueprintable)
class PERFECTAI_API UBTService_PAI_Consideration : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PAI_Consideration(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UPROPERTY(EditAnywhere, Category = "Utility")
	TObjectPtr<UPAIResponseCurve> ResponseCurve;

	UPROPERTY(EditAnywhere, Category = "Utility")
	bool bInverseScore;

	float ComputeScore(const struct FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const;
	
protected:

	virtual float Score(const struct FPAIActionSelectorContext& Context, UBehaviorTreeComponent* BtComp) const;
};
