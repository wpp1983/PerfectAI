﻿#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUtiAiBehaviorSetEditor;
class FPerfectAIEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

};
