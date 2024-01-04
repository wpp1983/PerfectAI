// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "UtiAIComponent.generated.h"


class UUtiAIBehavior;
class UUtiAIBehaviorSet;

UCLASS(ClassGroup = AI, meta = (BlueprintSpawnableComponent))
class PERFECTAI_API UUtiAIComponent : public UBrainComponent
{
	GENERATED_UCLASS_BODY()

public:

	// Begin UBrainComponent overrides
	virtual void StartLogic() override;
	virtual void RestartLogic() override;
	virtual void StopLogic(const FString& Reason) override;
	virtual void PauseLogic(const FString& Reason) override;
	virtual EAILogicResuming::Type ResumeLogic(const FString& Reason) override;

	virtual bool IsRunning() const override;
	virtual bool IsPaused() const override;
	virtual void Cleanup() override;
	virtual void HandleMessage(const FAIMessage& Message) override;
	// End UBrainComponent overrides

	// Begin UActorComponent overrides
	virtual void UninitializeComponent() override;
	void SelectMaxScoreBehavior();
	// End UActorComponent overrides

	/** BEGIN UActorComponent overrides */
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	/** END UActorComponent overrides */

	void StartAI(UUtiAIBehaviorSet* BehaviorSetAsset);

	static bool RunUtiAIOnAIController(class AAIController* AIController, UUtiAIBehaviorSet* BehaviorSetAsset);

	FORCEINLINE AAIController* GetAIOwner() const { return AIOwner; }
protected:
	void ReSetTickDeltaTime();

protected:
	TObjectPtr<UUtiAIBehaviorSet> BehaviorSet;

    /** Predicted next DeltaTime*/
    float NextTickDeltaTime = 0.;
    /** Accumulated DeltaTime if ticked more than predicted next delta time */
    float AccumulatedTickDeltaTime = 0.0f;
    /** GameTime of the last DeltaTime request, used for debugging to output warnings about ticking */
    double LastRequestedDeltaTimeGameTime = 0.;


	TObjectPtr<UUtiAIBehavior> CurrentBehavior;
};
