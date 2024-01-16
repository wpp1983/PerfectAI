// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PAIResponseCurve.generated.h"

/**
 * 
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class PERFECTAI_API UPAIResponseCurve : public UObject
{
	GENERATED_BODY()

protected:
	static float Sanitize(const float y);

public:

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Slope;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Exponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float XShift;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float YShift;

	virtual float ComputeValue(const float x) const;
};

UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Linear"))
class PERFECTAI_API UPAILinearResponseCurve : public UPAIResponseCurve
{
	GENERATED_BODY()

	UPAILinearResponseCurve()
	{
		Slope = 1.f;
		Exponent = 0.f;
		XShift = 0.f;
		YShift = 0.f;
	}
	
public:
	FORCEINLINE virtual float ComputeValue(const float x) const override { return Sanitize((Slope * (x - XShift)) + YShift); }
};


UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Polynomial"))
class PERFECTAI_API UPAIPolynomialResponseCurve : public UPAIResponseCurve
{
	GENERATED_BODY()

	UPAIPolynomialResponseCurve()
	{
		Slope = 1.f;
		Exponent = 1.f;
		XShift = 0.f;
		YShift = 0.f;
	}

public:
	FORCEINLINE virtual float ComputeValue(const float x) const override { return Sanitize((Slope * FMath::Pow(x - XShift, Exponent)) + YShift); }
};

UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Logistic"))
class PERFECTAI_API UPAILogisticResponseCurve : public UPAIResponseCurve
{
	GENERATED_BODY()

	UPAILogisticResponseCurve()
	{
		Slope = 1.f;
		Exponent = 1.f;
		XShift = 0.f;
		YShift = 0.f;
	}
	
public:
	FORCEINLINE virtual float ComputeValue(const float x) const override { return Sanitize((Slope / (1.f + FMath::Exp(-10.f * Exponent * (x - 0.5f - XShift)))) + YShift); }
};

UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Logit"))
class PERFECTAI_API UPAILogitResponseCurve : public UPAIResponseCurve
{
	GENERATED_BODY()
	
	UPAILogitResponseCurve()
	{
		Slope = 1.f;
		Exponent = 0.f;
		XShift = 0.f;
		YShift = 0.f;
	}

public:
	FORCEINLINE virtual float ComputeValue(const float x) const override { return Sanitize(Slope * FMath::Loge((x - XShift) / (1.0 - (x - XShift))) / 5.0 + 0.5 + YShift); }
};

UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Normal"))
class PERFECTAI_API UPAINormalResponseCurve : public UPAIResponseCurve
{
	GENERATED_BODY()

	UPAINormalResponseCurve()
	{
		Slope = 0.f;
		Exponent = 1.f;
		XShift = 0.f;
		YShift = 0.f;
	}

public:
	FORCEINLINE virtual float ComputeValue(const float x) const override
	{
		return Sanitize(Slope * FMath::Exp(-30.0 * Exponent * (x - XShift - 0.5) * (x - XShift - 0.5)) + YShift);
	}
};

UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Sine"))
class PERFECTAI_API UPAISineResponseCurve : public UPAIResponseCurve
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual float ComputeValue(const float x) const override { return Sanitize(0.5 * Slope * FMath::Sin(2.0 * UE_PI * (x - XShift)) + 0.5 + YShift); }
};

UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Constant"))
class PERFECTAI_API UPAIConstantResult : public UPAIResponseCurve
{
	GENERATED_BODY()

public:
	/* Only Value considered */
	UPROPERTY(EditAnywhere, Category = "Settings")
	float StaticValue;

	FORCEINLINE virtual float ComputeValue(const float x) const override { return Sanitize(StaticValue); }
};