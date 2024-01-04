// Fill out your copyright notice in the Description page of Project Settings.


#include "UtiAIBehaviorSetFactory.h"

#include "UtilityAI/UtiAIBehaviorSet.h"

UUtiAIBehaviorSetFactory::UUtiAIBehaviorSetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UUtiAIBehaviorSet::StaticClass();
}


UObject* UUtiAIBehaviorSetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UUtiAIBehaviorSet::StaticClass()));
	return NewObject<UUtiAIBehaviorSet>(InParent, Class, Name, Flags);;
}

bool UUtiAIBehaviorSetFactory::CanCreateNew() const
{
	return true;
}
