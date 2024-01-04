// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/UtiAIComponent.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UtilityAI/UtiAI.h"
#include "UtilityAI/UtiAIBehaviorSet.h"
#include "UtilityAI/UtiAIBehavior.h"

DEFINE_LOG_CATEGORY(LogUtiAI)

DEFINE_STAT(STAT_AI_UtiAI_Tick);

UUtiAIComponent::UUtiAIComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);

	NextTickDeltaTime = 0.0f;
}


void UUtiAIComponent::StartLogic()
{
	Super::StartLogic();
}

void UUtiAIComponent::RestartLogic()
{
	Super::RestartLogic();
}

void UUtiAIComponent::StopLogic(const FString& Reason)
{
	Super::StopLogic(Reason);
}

void UUtiAIComponent::PauseLogic(const FString& Reason)
{
	Super::PauseLogic(Reason);
}

EAILogicResuming::Type UUtiAIComponent::ResumeLogic(const FString& Reason)
{
	return Super::ResumeLogic(Reason);
}

bool UUtiAIComponent::IsRunning() const
{
	return Super::IsRunning();
}

bool UUtiAIComponent::IsPaused() const
{
	return Super::IsPaused();
}

void UUtiAIComponent::Cleanup()
{
	Super::Cleanup();
}

void UUtiAIComponent::HandleMessage(const FAIMessage& Message)
{
	Super::HandleMessage(Message);
}

void UUtiAIComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void UUtiAIComponent::SelectMaxScoreBehavior()
{
	if (BehaviorSet != nullptr)
	{
		FUtiAIScoreData MaxScore;
		UUtiAIBehavior* MaxScoreBehavior = nullptr;
		for (auto Behavior : BehaviorSet->Behaviors)
		{
			if (Behavior != nullptr)
			{
				auto Score = Behavior->GetUtilityScore();
				if (Score > MaxScore)
				{
					MaxScore = Score;
					MaxScoreBehavior = Behavior;
				}
			}
		}

		if (MaxScoreBehavior != nullptr)
		{
			CurrentBehavior = MaxScoreBehavior;
			CurrentBehavior->Start(*this);

			UE_VLOG(GetOwner(), LogUtiAI, Display, TEXT("UtiAI(%i) selected behavior %s with score %f."), GFrameCounter, *CurrentBehavior->GetName(), MaxScore.FinalScore);
		}
	}
}

void UUtiAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Warn if asked to be ticked the next frame and did not.
	if (NextTickDeltaTime == 0.0f)
	{
		UWorld* MyWorld = GetWorld();
		if (MyWorld)
		{
			const double CurrentGameTime = MyWorld->GetTimeSeconds();
			const float CurrentDeltaTime = MyWorld->GetDeltaSeconds();
			if (CurrentGameTime - LastRequestedDeltaTimeGameTime - CurrentDeltaTime > KINDA_SMALL_NUMBER)
			{
				UE_VLOG(GetOwner(), LogUtiAI, Error,
				        TEXT(
					        "UtiAI(%i) expected to be tick next frame, current deltatime(%f) and calculated deltatime(%f)."
				        ), GFrameCounter, CurrentDeltaTime, CurrentGameTime - LastRequestedDeltaTimeGameTime);
			}
		}
	}

	// Check if we really have reached the asked DeltaTime, 
	// If not then accumulate it and reschedule
	NextTickDeltaTime -= DeltaTime;
	if (NextTickDeltaTime > 0.0f)
	{
		// The TickManager is using global time to calculate delta since last ticked time. When the value is big, we can get into float precision errors compare to our calculation.
		if (NextTickDeltaTime > KINDA_SMALL_NUMBER)
		{
			UE_VLOG(GetOwner(), LogUtiAI, Error,
			        TEXT("UtiAI(%i) did not need to be tick, ask deltatime of %fs got %fs with a diff of %fs."),
			        GFrameCounter, NextTickDeltaTime + AccumulatedTickDeltaTime + DeltaTime,
			        DeltaTime + AccumulatedTickDeltaTime, NextTickDeltaTime);
		}
		AccumulatedTickDeltaTime += DeltaTime;
		return;
	}

	bool bDoneSomething = MessagesToProcess.Num() > 0;
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SCOPE_CYCLE_COUNTER(STAT_AI_Overall);
	SCOPE_CYCLE_COUNTER(STAT_AI_UtiAI_Tick);

	check(IsValid(this));

	if (CurrentBehavior != nullptr)
	{
		CurrentBehavior->Tick(DeltaTime);
	}
	else
	{
		DeltaTime += AccumulatedTickDeltaTime;
		AccumulatedTickDeltaTime = 0.0f;

		SelectMaxScoreBehavior();
	}
	

	if (!bDoneSomething)
	{
		UE_VLOG(GetOwner(), LogUtiAI, Error, TEXT("UtiAI(%i) planned to do something but actually did not."),
		        GFrameCounter);
	}

	ReSetTickDeltaTime();
}

void UUtiAIComponent::StartAI(UUtiAIBehaviorSet* BehaviorSetAsset)
{
	BehaviorSet = DuplicateObject<UUtiAIBehaviorSet>(BehaviorSetAsset, this);
}

bool UUtiAIComponent::RunUtiAIOnAIController(AAIController* AIController, UUtiAIBehaviorSet* BehaviorSetAsset)
{
	if (BehaviorSetAsset == NULL)
	{
		UE_VLOG(AIController, LogUtiAI, Warning, TEXT("RunUtiAIOnAIController: Unable to run NULL AI"));
		return false;
	}
	
	bool bSuccess = true;
	
	// see if need a blackboard component at all
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (BehaviorSetAsset->BlackboardAsset && ( AIController->GetBlackboardComponent() == nullptr ||  AIController->GetBlackboardComponent()->IsCompatibleWith(BehaviorSetAsset->BlackboardAsset) == false))
	{
		bSuccess = AIController->UseBlackboard(BehaviorSetAsset->BlackboardAsset, BlackboardComp);
	}

	if (bSuccess)
	{
		UUtiAIComponent* UtiAIComponent = Cast<UUtiAIComponent>(AIController->GetBrainComponent());
		if (UtiAIComponent == nullptr)
		{
			UE_VLOG(AIController, LogUtiAI, Log, TEXT("RunUtiAIOnAIController: spawning UUtiAIComponent.."));

			UtiAIComponent = NewObject<UUtiAIComponent>(AIController, TEXT("UtiAIComponent"));
			UtiAIComponent->RegisterComponent();
			REDIRECT_OBJECT_TO_VLOG(UtiAIComponent, AIController);
		}
		
		// make sure BrainComponent points at the newly created component
		AIController->BrainComponent = UtiAIComponent;

		check(UtiAIComponent != NULL);
		UtiAIComponent->StartAI(BehaviorSetAsset);
	}

	return bSuccess;
}

void UUtiAIComponent::ReSetTickDeltaTime()
{
	NextTickDeltaTime = 1.0f;
	
	UWorld* MyWorld = GetWorld();
	LastRequestedDeltaTimeGameTime = MyWorld ? MyWorld->GetTimeSeconds() : 0.;
}
