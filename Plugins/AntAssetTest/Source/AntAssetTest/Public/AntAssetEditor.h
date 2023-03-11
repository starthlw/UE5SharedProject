#pragma once

#include "CoreMinimal.h"
#include "Toolkits/SimpleAssetEditor.h"
#include "Misc/NotifyHook.h"
#include "AntAsset.h"
#include "AntAssetEditorViewport.h"

class FEditorViewportTabContent;
class IDetailsView;
class FTabManager;
class IToolkitHost;

class FAntAssetEditorToolkit : public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public:
    void InitAntAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);

public:
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;

    virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
    virtual FString GetReferencerName() const override
    {
        return TEXT("FAntAssetEditorToolkit");
    }

    static TSharedPtr<FAntAssetEditorToolkit> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitTookitHost, UObject* ObjectToEdit);

private:
    void ExtendToolbar();
    void FillToolbar(FToolBarBuilder& ToolbarBuilder, const TSharedRef<FUICommandList> InToolkitCommands);

    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
    void BindCommands();

    TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);

    void OnPropertyChanged(const FPropertyChangedEvent& InEvent);

public:
    UAntAsset* AntAsset;

private:
    static const FName ViewportTabId;
    static const FName PropertiesTabId;

    TSharedPtr<FEditorViewportTabContent> ViewportTabContent;
    TSharedPtr<IDetailsView> AntAssetDetailsView;
    TSharedPtr<SAntAssetEditorViewport> AntAssetViewport;
};