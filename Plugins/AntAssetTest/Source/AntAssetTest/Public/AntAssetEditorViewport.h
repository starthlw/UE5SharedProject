#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"
#include "SAssetEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class FAntAssetEditorToolkit;
class FAdvancedPreviewScene;
class FEditorViewportClient;
class SEditorViewport;
class UAntAsset;

class SAntAssetEditorViewport : public SAssetEditorViewport, public ICommonEditorViewportToolbarInfoProvider, public FGCObject
{
public:
    SLATE_BEGIN_ARGS(SAntAssetEditorViewport) {}
        SLATE_ARGUMENT(TWeakPtr<FAntAssetEditorToolkit>, AntAssetEditorToolkit)
    SLATE_END_ARGS()

    SAntAssetEditorViewport();

    void Construct(const FArguments& InArgs);
    void UpdateViewport(TSharedPtr<FAntAssetEditorToolkit> AntAssetEditorToolkit);
    void GenerateSphere(UAntAsset* AntAsset);

    virtual TSharedRef<SEditorViewport> GetViewportWidget() override;
    virtual TSharedPtr<FExtender> GetExtenders() const override;
    virtual void OnFloatingButtonClicked() override;

    virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
    virtual FString GetReferencerName() const override
    {
        return TEXT("SAntAssetEditorViewport");
    }

protected:
    virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
    virtual TSharedPtr<SWidget> MakeViewportToolbar() override;

private:
    TSharedPtr<FAdvancedPreviewScene> PreviewScene;
    TSharedPtr<FEditorViewportClient> EditorViewportClient;
    TWeakPtr<FAntAssetEditorToolkit> AntAssetEditorToolkitPtr;
};


class FAntAssetEditorViewportClient : public FEditorViewportClient
{
public:
    using Super = FEditorViewportClient;

    FAntAssetEditorViewportClient(FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);
    virtual void Tick(float DeltaSeconds) override;
};