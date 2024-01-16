#pragma once

#include "CoreMinimal.h"

#include "Logging/LogMacros.h"
#include "Stats/Stats.h"

#if UE_BUILD_SHIPPING
DECLARE_LOG_CATEGORY_EXTERN(LogPAI, Warning, Warning);
#else
DECLARE_LOG_CATEGORY_EXTERN(LogPAI, Log, All);
#endif

#if STATS
DECLARE_STATS_GROUP(TEXT("PAI"), STATGROUP_PAI, STATCAT_Advanced);
#endif
