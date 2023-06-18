// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntTestEdModeToolkit.h"
#include "AntTestEdModeObject.h"
#include "Modules/ModuleManager.h"
#include "EditorModeManager.h"
#include "EditorModes.h"

#define LOCTEXT_NAMESPACE "AntTestEdMode"

void FAntTestEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	AntTestEditor = SNew(SAntTestEditor, SharedThis(this));
	FModeToolkit::Init(InitToolkitHost);
}
TSharedPtr<class FUICommandList> FAntTestEdModeToolkit::GetToolkitCommands() const
{
    return TSharedPtr<FUICommandList>();
}

TSharedPtr<SWidget> FAntTestEdModeToolkit::GetInlineContent() const
{
	return 	AntTestEditor;
}

FName FAntTestEdModeToolkit::GetToolkitFName() const
{
	return FName("AntTestEdMode");
}

FText FAntTestEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("Test Toolkit", "DisplayName", "Test Tool");
}

FAntTestEdMode* FAntTestEdModeToolkit::GetEditorMode() const
{
	return (FAntTestEdMode*)GLevelEditorModeTools().GetActiveMode(FAntTestEdMode::EM_AntTestEdModeId);
}

void FAntTestEdModeToolkit::RefreshDetailPanel()
{ 
    AntTestEditor->RefreshDetailPanel(); 
}

void SAntTestEditor::Construct(const FArguments& InArgs, TSharedRef<FAntTestEdModeToolkit> InParentToolkit)
{
    ParentToolkit = InParentToolkit;

    FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
    DetailsViewArgs.bAllowSearch = false;

    DetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    DetailsPanel->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateSP(this, &SAntTestEditor::GetIsPropertyVisible));

    FAntTestEdMode* EdMode = GetEditorMode();
    if (EdMode)
    {
        DetailsPanel->SetObject((EdMode->UISettings));
    }

    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(STextBlock)
            .Text(FText::FromString(TEXT("AntTestEdMode Panel")))
        ]
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            [
                DetailsPanel.ToSharedRef()
            ]
        ]
    ];
}

void SAntTestEditor::RefreshDetailPanel()
{
    FAntTestEdMode* EdMode = GetEditorMode();
    if (EdMode)
    {
        DetailsPanel->SetObject((EdMode->UISettings));
    }
}

bool SAntTestEditor::GetEditorIsEnabled() const
{
	return true;
}

bool SAntTestEditor::GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const
{
	if (PropertyAndParent.Property.HasMetaData("hide"))
		return false;
	return true;
}

FAntTestEdMode* SAntTestEditor::GetEditorMode() const
{
	return (FAntTestEdMode*)GLevelEditorModeTools().GetActiveMode(FAntTestEdMode::EM_AntTestEdModeId);
}

#undef LOCTEXT_NAMESPACE
