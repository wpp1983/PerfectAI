// Copyright Epic Games, Inc. All Rights Reserved.

#include "PerfectAI.h"

#include "..\Public\UtilityAI\BTService_PAI_Consideration.h"
#include "UtilityAI/DetailCustomization/PAIBTService_ConsiderationDetails.h"

#define LOCTEXT_NAMESPACE "FPerfectAIModule"

void FPerfectAIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if WITH_EDITOR
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UBTService_PAI_Consideration::StaticClass()->GetFName(),
											 FOnGetDetailCustomizationInstance::CreateStatic(&FPAIBTService_ConsiderationDetails::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
#endif
}

void FPerfectAIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPerfectAIModule, PerfectAI)