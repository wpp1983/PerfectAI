// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR
#include "CoreMinimal.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"

class FPAIBTService_ConsiderationDetails : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	TSharedPtr<class SResponseCurveWidget> PreviewWidget;
};

#endif
