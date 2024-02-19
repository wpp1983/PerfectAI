// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAI/Tools/UtilityAIToolsHelper.h"

#include "BehaviorTree/BehaviorTree.h"
#include "UtilityAI/BTComposite_PAI_Brain.h"
#include "UtilityAI/BTTask_PAI_Action.h"


struct UtilityAIToJsonData_Consideration
{
	FString NodeName;	
};

struct UtilityAIToJsonData_Action
{
	FString NodeName;

	TArray<UtilityAIToJsonData_Consideration> Considerations;
};



struct UtilityAIToJsonData
{
	FString BrainName;

	TArray<UtilityAIToJsonData_Action> Actions;
};

FString UUtilityAIToolsHelper::ExportUtilityAIToJson(UBehaviorTree* BehaviorTree)
{
	if (BehaviorTree != nullptr && BehaviorTree->RootNode != nullptr)
	{
		UtilityAIToJsonData ExportData;
		auto RootNode = BehaviorTree->RootNode;
		UBTComposite_PAI_Brain* Brain = nullptr;
		for (int32 Idx = 0; Idx < RootNode->GetChildrenNum(); ++Idx)
		{
			auto ChildComposite = Cast<UBTComposite_PAI_Brain>(RootNode->Children[Idx].ChildComposite);
			
			if (ChildComposite != nullptr)
			{
				Brain = ChildComposite;
				break;
			}
		}
		if (Brain == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Brain found in BehaviorTree %s"), *BehaviorTree->GetName());
			return "";
		}

		ExportData.BrainName = Brain->GetNodeName();

		for (int32 ActionIndex = 0; ActionIndex < Brain->GetChildrenNum(); ++ActionIndex)
		{
			auto ChildAction = Cast<UBTTask_PAI_Action>(Brain->GetChildNode(ActionIndex));
			if (ChildAction != nullptr)
			{
				UtilityAIToJsonData_Action ActionData;
				ActionData.NodeName = ChildAction->GetNodeName();

				ExportData.Actions.Add(ActionData);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Child %s Is No Action"), *ChildAction->GetNodeName());
			}
			
		}
		
		
	}
	

	return "";
}
