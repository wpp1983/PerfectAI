// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR
#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SLeafWidget.h"

class FPaintArgs;
class FSlateWindowElementList;

/**
 * 
 */
class SResponseCurveWidget : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SResponseCurveWidget) {}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
						  int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	TWeakObjectPtr<class UPAIResponseCurve> ResponseCurve;

private:
	FVector2D GetWidgetPosition(float X, float Y, const FGeometry& Geom) const;
};

#endif
