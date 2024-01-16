// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/PAIResponseCurve.h"

float UPAIResponseCurve::Sanitize(const float y)
{
	if (!FMath::IsFinite(y))
	{
		return 0.0;
	}

	if (y < 0.0)
	{
		return 0.0;
	}

	if (y > 1.0)
	{
		return 1.0;
	}

	return y;
}

float UPAIResponseCurve::ComputeValue(const float x) const
{
	return 0.0;
}
