// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/UtiAIBehavior.h"
#include "UtilityAI/UtiAIConsideration.h"
#include "UtilityAI/UtiAITask.h"

FUtiAIScoreData UUtiAIBehavior::GetUtilityScore()
{
	FUtiAIScoreData Score;

	for (const auto Consideration : Considerations)
	{
		Score.Multiply(Consideration->GetScore());
	}
	
	return Score;
}

void UUtiAIBehavior::Start(UUtiAIComponent& OwnerComp)
{
	if (Task != nullptr)
	{
		Task->ExecuteTask(OwnerComp);
	}
	
}

void UUtiAIBehavior::Tick(float DeltaTime)
{
	
}

bool UUtiAIBehavior::IsFinish() const
{
	return true;
}

FString UUtiAIBehavior::GetDescription() const
{
	return GetName();
}
