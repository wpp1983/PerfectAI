// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/BTTask_PAI_Action.h"

UBTTask_PAI_Action::UBTTask_PAI_Action(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	NodeName = TEXT("PAI Action");
}

FString UBTTask_PAI_Action::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}

uint16 UBTTask_PAI_Action::GetInstanceMemorySize() const
{
	return sizeof(FPAI_ActionMemory);
}
