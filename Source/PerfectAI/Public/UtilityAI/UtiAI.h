

#pragma once

PERFECTAI_API DECLARE_LOG_CATEGORY_EXTERN(LogUtiAI, Display, All);


DECLARE_STATS_GROUP(TEXT("Behavior Tree"), STATGROUP_AIUtiAI, STATCAT_Advanced);

DECLARE_CYCLE_STAT_EXTERN(TEXT("UtiAI Tick"),STAT_AI_UtiAI_Tick,STATGROUP_AIUtiAI, );


UENUM(BlueprintType)
enum EUtiAITaskResult : uint8
{
	// finished as success
	Succeeded,
	// finished as failure
	Failed,
	// finished aborting = failure
	Aborted,
	// not finished yet
	InProgress,
};


