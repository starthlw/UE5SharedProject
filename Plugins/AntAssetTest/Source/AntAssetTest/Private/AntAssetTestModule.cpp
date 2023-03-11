// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntAssetTestModule.h"
#include "AntAssetTestStyle.h"
#include "AntAssetEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "AssetToolsModule.h"
#include "AntAssetEditor.h"
#include "AntAsset_AssetTypeAction.h"
#include "AntAssetThumbnailRenderer.h"

static const FName AntAssetTestTabName("AntAssetTest");

#define LOCTEXT_NAMESPACE "FAntAssetTestModule"

EAssetTypeCategories::Type FAntAssetTestModule::AntAssetCategory;

void FAntAssetTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAntAssetTestStyle::Initialize();
	FAntAssetTestStyle::ReloadTextures();

	FAntAssetEditorCommands::Register();

    // Helper lambda for registering asset type actions for automatic cleanup on shutdown
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    auto RegisterAssetTypeAction = [&](TSharedRef<IAssetTypeActions> Action)
    {
        AssetTools.RegisterAssetTypeActions(Action);
        CreatedAssetTypeActions.Add(Action);
    };
    RegisterAssetTypeAction(MakeShareable(new FAntAsset_AssetTypeAction));
	AntAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("AntAsset")), LOCTEXT("AntAssetCategory", "AntAsset"));

	UThumbnailManager::Get().RegisterCustomRenderer(UAntAsset::StaticClass(), UAntAssetThumbnailRenderer::StaticClass());
}

void FAntAssetTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

    if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
    {
        IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
        for (auto CreatedAssetTypeAction : CreatedAssetTypeActions)
        {
            AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeAction.ToSharedRef());
        }
    }
    CreatedAssetTypeActions.Empty();

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAntAssetTestStyle::Shutdown();

	FAntAssetEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AntAssetTestTabName);
}

TSharedRef<FAntAssetEditorToolkit> FAntAssetTestModule::CreateAntAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* AntAsset)
{
    TSharedRef<FAntAssetEditorToolkit> NewAntAssetEditor(new FAntAssetEditorToolkit());
	NewAntAssetEditor->InitAntAssetEditor(Mode, InitToolkitHost, AntAsset);
    return NewAntAssetEditor;
}

TSharedRef<SDockTab> FAntAssetTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FAntAssetTestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("AntAssetTest.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FAntAssetTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AntAssetTestTabName);
}

//void FAntAssetTestModule::RegisterMenus()
//{
//	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
//	FToolMenuOwnerScoped OwnerScoped(this);
//
//	{
//		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
//		{
//			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
//			Section.AddMenuEntryWithCommandList(FAntAssetEditorCommands::Get().OpenPluginWindow, PluginCommands);
//		}
//	}
//
//	{
//		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
//		{
//			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
//			{
//				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAntAssetEditorCommands::Get().OpenPluginWindow));
//				Entry.SetCommandList(PluginCommands);
//			}
//		}
//	}
//}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAntAssetTestModule, AntAssetTest)