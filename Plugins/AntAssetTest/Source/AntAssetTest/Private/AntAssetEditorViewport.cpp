// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntAssetEditorViewport.h"

#include "AntAssetEditor.h"
#include "AdvancedPreviewScene.h"
#include "PreviewScene.h"
#include "UObject/ObjectMacros.h"
#include "EditorViewportClient.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "AntAssetTestModule.h"
#include "SEditorViewport.h"
#include "AssetViewerSettings.h"

SAntAssetEditorViewport::SAntAssetEditorViewport()
{
}

void SAntAssetEditorViewport::Construct(const FArguments& InArgs)
{
    AntAssetEditorToolkitPtr = InArgs._AntAssetEditorToolkit;

    TSharedPtr<FAntAssetEditorToolkit> AntAssetEditorToolkit = AntAssetEditorToolkitPtr.Pin();
    check(AntAssetEditorToolkitPtr.IsValid());

    PreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
    PreviewScene->SetFloorVisibility(false);
    
    GenerateSphere(AntAssetEditorToolkit->AntAsset);
    SEditorViewport::Construct(SEditorViewport::FArguments());
}

void SAntAssetEditorViewport::UpdateViewport(TSharedPtr<FAntAssetEditorToolkit> AntAssetEditorToolkit)
{
    if (EditorViewportClient.IsValid() && PreviewScene.IsValid())
    {
        UAssetViewerSettings* Setting = UAssetViewerSettings::Get();
        const int32 ProfilesIndex = PreviewScene->GetCurrentProfileIndex();
        if (Setting->Profiles.IsValidIndex(ProfilesIndex))
        {
            GenerateSphere(AntAssetEditorToolkit->AntAsset);
            PreviewScene->UpdateScene(Setting->Profiles[ProfilesIndex]);
        }
    }
}

void SAntAssetEditorViewport::GenerateSphere(UAntAsset* AntAsset)
{
    if (!AntAsset)
    {
        return;
    }

    for (auto& Ele : AntAsset->ViewportComponents)
    {
        PreviewScene->RemoveComponent(Ele.Component);
    }
    AntAsset->ViewportComponents.Empty();

    FRichCurve* Curve = AntAsset->ScaleCurve.GetRichCurve();
    if (AntAsset->Mesh)
    {
        for (uint32 i = 0; i < AntAsset->Num; i++)
        {
            UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient);
            Component->SetMobility(EComponentMobility::Static);
            FComponentReregisterContext ReregisterContext(Component);
            Component->SetStaticMesh(AntAsset->Mesh);
            FTransform Transform;
            Transform.SetLocation(FVector(0, i * 100, i * 100 * Curve->Eval(i * 1.0 / AntAsset->Num)));
            PreviewScene->AddComponent(Component, Transform);
            AntAsset->ViewportComponents.Add(ViewportObject(Component, Transform));
        }
    }
}

TSharedRef<SEditorViewport> SAntAssetEditorViewport::GetViewportWidget()
{
    return SharedThis(this);
}

TSharedPtr<FExtender> SAntAssetEditorViewport::GetExtenders() const
{
    TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
    return Result;
}

void SAntAssetEditorViewport::OnFloatingButtonClicked()
{
}

void SAntAssetEditorViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
}

TSharedRef<FEditorViewportClient> SAntAssetEditorViewport::MakeEditorViewportClient()
{
    EditorViewportClient = MakeShareable(new FAntAssetEditorViewportClient(PreviewScene.Get(), SharedThis(this)));
    EditorViewportClient->SetRealtime(true);//
    return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SAntAssetEditorViewport::MakeViewportToolbar()
{
    return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}


// ----------------------------------------------------------------------------------

FAntAssetEditorViewportClient::FAntAssetEditorViewportClient(FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget)
    : FEditorViewportClient(nullptr, InPreviewScene, InEditorViewportWidget)
{
    bSetListenerPosition = false;
    SetRealtime(true);
    EngineShowFlags.Grid = false;
    //FVector(-3000, 0, 2000), FRotator(-35.f, 0.f, 0.f)
    SetViewLocation(FVector(-3000, 0, 2000));
    SetViewRotation(FRotator(-35.f, 0.f, 0.f));
}

void FAntAssetEditorViewportClient::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Tick the preview scene world.
    if (!GIntraFrameDebuggingGameThread)
    {
        PreviewScene->GetWorld()->Tick(IsRealtime() ? LEVELTICK_All : LEVELTICK_TimeOnly, DeltaSeconds);
    }
}

