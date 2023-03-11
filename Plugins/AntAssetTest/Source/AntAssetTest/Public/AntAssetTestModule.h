#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"
#include "IAssetTypeActions.h"

class FToolBarBuilder;
class FMenuBuilder;
class FAntAssetEditorToolkit;

class FAntAssetTestModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static EAssetTypeCategories::Type GetAssetCategory() { return AntAssetCategory; }
    TSharedRef<FAntAssetEditorToolkit> CreateAntAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UObject* AntAsset);
	void PluginButtonClicked();
	
private:
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	static EAssetTypeCategories::Type AntAssetCategory;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
