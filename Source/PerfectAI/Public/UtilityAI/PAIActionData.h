#pragma once
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "PAIActionData.generated.h"

USTRUCT()
struct FPAIActionData
{
	GENERATED_BODY();

	float InitialWeight = 0.f;
	float LastExecutionTime = 0.f;
	float CompensationFactor = 0.f;

	TArray<class UBTService_PAI_Consideration*> Considerations;	
};

USTRUCT(BlueprintType)
struct FPAIActionSelectorContext
{
	GENERATED_BODY();
	
	class PAIActionSelector* Selector = nullptr;
	AActor* Target = nullptr;
	class AAIController* AIController = nullptr;
	float TotalScore = 0.f;
	int32 ActionIndex = BTSpecialChild::NotInitialized;
};

class PAIActionSelector
{
public:
	TArray<FPAIActionData>	ActionsData;
	TMap<FString, int32>	ActionNameIndexMap;

	void AddAction(const FPAIActionData& InActionData, const FString& Name);
	FPAIActionSelectorContext ChooseBehavior(class AAIController* Controller, UBehaviorTreeComponent* BtComp,
		const TArray<class AActor*>& Targets);
};
