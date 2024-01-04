#pragma once
#include "CoreMinimal.h"

#include "UtiAIScoreData.generated.h"

USTRUCT()
struct PERFECTAI_API FUtiAIScoreData
{
	GENERATED_BODY()

	FUtiAIScoreData()
		: FinalScore(0.0f)
	{
	}
	
	float FinalScore;

	void Multiply(const FUtiAIScoreData& Other)
	{
		FinalScore *= Other.FinalScore;
	}

	bool operator>(const FUtiAIScoreData& Other) const
	{
		return FinalScore > Other.FinalScore;
	}
};
