#if WITH_EDITOR
#include "PAIBTService_ConsiderationDetails.h"


#include "Editor/PropertyEditor/Public/DetailCategoryBuilder.h"
#include "Editor/PropertyEditor/Public/DetailLayoutBuilder.h"
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"

#include "SResponseCurveWidget.h"
#include "UtilityAI\BTService_PAI_Consideration.h"

#define LOCTEXT_NAMESPACE "PAIBTService_ConsiderationDetails"

TSharedRef<IDetailCustomization> FPAIBTService_ConsiderationDetails::MakeInstance()
{
	return MakeShareable(new FPAIBTService_ConsiderationDetails);
}

void FPAIBTService_ConsiderationDetails::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TWeakObjectPtr<UBTService_PAI_Consideration> Consideration;
	TArray<TWeakObjectPtr<UObject>> EditedObjects;
	DetailLayout.GetObjectsBeingCustomized(EditedObjects);
	for (int32 i = 0; i < EditedObjects.Num(); i++)
	{
		const UBTService_PAI_Consideration* EditedTest = Cast<const UBTService_PAI_Consideration>(EditedObjects[i].Get());
		if (EditedTest)
		{
			Consideration = MakeWeakObjectPtr(const_cast<UBTService_PAI_Consideration*>(EditedTest));
			break;
		}
	}

	// scoring & filter function preview
	IDetailCategoryBuilder& PreviewCategory = DetailLayout.EditCategory("Preview");
	PreviewCategory.AddCustomRow(LOCTEXT("Preview", "Preview")).WholeRowWidget[SAssignNew(PreviewWidget, SResponseCurveWidget)];

	PreviewWidget->ResponseCurve = Consideration->ResponseCurve;
}

#undef LOCTEXT_NAMESPACE
#endif
