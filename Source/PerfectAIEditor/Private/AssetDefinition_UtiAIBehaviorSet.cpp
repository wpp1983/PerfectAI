// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetDefinition_UtiAIBehaviorSet.h"

#include "UtilityAI/UtiAIBehaviorSet.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

FText UAssetDefinition_UtiAIBehaviorSet::GetAssetDisplayName() const
{
	return LOCTEXT("UAssetDefinition_UtiAIBehaviorSet", "UtiAI BehaviorSet");
}

FLinearColor UAssetDefinition_UtiAIBehaviorSet::GetAssetColor() const
{
	return FColor(149,70,255);
}

TSoftClassPtr<> UAssetDefinition_UtiAIBehaviorSet::GetAssetClass() const
{
	return UUtiAIBehaviorSet::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_UtiAIBehaviorSet::GetAssetCategories() const
{
	static const FAssetCategoryPath Categories[] = { EAssetCategoryPaths::AI };
	return Categories;
}

EAssetCommandResult UAssetDefinition_UtiAIBehaviorSet::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	const EToolkitMode::Type Mode = OpenArgs.GetToolkitMode();

	for (UUtiAIBehaviorSet* Asset: OpenArgs.LoadObjects<UUtiAIBehaviorSet>())
	{
		// check if we have an editor open for this BT's blackboard & use that if we can
		bool bFoundExisting = false;
		if (Asset->BlackboardAsset != nullptr)
		{
			// constexpr bool bFocusIfOpen = false;
			// FBehaviorTreeEditor* ExistingInstance = static_cast<FBehaviorTreeEditor*>(GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(BehaviorTree->BlackboardAsset, bFocusIfOpen));
			// if (ExistingInstance != nullptr && ExistingInstance->GetBehaviorTree() == nullptr)
			// {
			// 	ExistingInstance->InitBehaviorTreeEditor(Mode, OpenArgs.ToolkitHost, BehaviorTree);
			// 	bFoundExisting = true;
			// }
		}

		if (!bFoundExisting)
		{
			// FBehaviorTreeEditorModule& BehaviorTreeEditorModule = FModuleManager::GetModuleChecked<FBehaviorTreeEditorModule>("BehaviorTreeEditor");
			// BehaviorTreeEditorModule.CreateBehaviorTreeEditor(Mode, OpenArgs.ToolkitHost, BehaviorTree);
		}
	}
	return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE