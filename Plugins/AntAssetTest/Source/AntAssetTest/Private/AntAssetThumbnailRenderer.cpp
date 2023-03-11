#include "AntAssetThumbnailRenderer.h"
#include "Misc/App.h"
#include "ShowFlags.h"
#include "SceneView.h"
#include "Engine/StaticMesh.h"
#include "AntAsset.h"
#include "ThumbnailRendering/SceneThumbnailInfo.h"

UAntAssetThumbnailRenderer::UAntAssetThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ThumbnailScene = nullptr;
}

void UAntAssetThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
    UAntAsset* AntAsset = Cast<UAntAsset>(Object);
    if (IsValid(AntAsset))
    {
        if (ThumbnailScene == nullptr || ensure(ThumbnailScene->GetWorld() != nullptr) == false)
        {
            if (ThumbnailScene)
            {
                FlushRenderingCommands();
                delete ThumbnailScene;
            }
            ThumbnailScene = new FAntAssetThumbnailScene();
        }

        if (AntAsset->Mesh)
        {
            for (auto& Ele : AntAsset->ViewportComponents)
            {
                ThumbnailScene->AddComponent(Ele.Component, Ele.Transform);
                ThumbnailScene->Bounds = ThumbnailScene->Bounds + Ele.Component->Bounds;
            }
            ThumbnailScene->StaticMesh = AntAsset->Mesh;
        }

        ThumbnailScene->GetScene()->UpdateSpeedTreeWind(0.0);

        FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(RenderTarget, ThumbnailScene->GetScene(), FEngineShowFlags(ESFIM_Game))
            .SetTime(UThumbnailRenderer::GetTime())
            .SetAdditionalViewFamily(bAdditionalViewFamily));

        ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
        ViewFamily.EngineShowFlags.MotionBlur = 0;
        ViewFamily.EngineShowFlags.LOD = 0;

        ThumbnailScene->SetStaticMesh(AntAsset->Mesh);
        RenderViewFamily(Canvas, &ViewFamily, ThumbnailScene->CreateView(&ViewFamily, X, Y, Width, Height));
        ThumbnailScene->SetStaticMesh(nullptr);
    }
}

void UAntAssetThumbnailRenderer::BeginDestroy()
{
    if (ThumbnailScene != nullptr)
    {
        delete ThumbnailScene;
        ThumbnailScene = nullptr;
    }

    Super::BeginDestroy();
}

void FAntAssetThumbnailScene::GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const
{
    const float HalfFOVRadians = FMath::DegreesToRadians<float>(InFOVDegrees) * 0.5f;
    // Add extra size to view slightly outside of the sphere to compensate for perspective
    const float HalfMeshSize = Bounds.SphereRadius * 1.15;
    const float BoundsZOffset = GetBoundsZOffset(Bounds);
    const float TargetDistance = HalfMeshSize / FMath::Tan(HalfFOVRadians);

    if (!StaticMesh)
    {
        return;
    }

    USceneThumbnailInfo* ThumbnailInfo = Cast<USceneThumbnailInfo>(StaticMesh->ThumbnailInfo);
    if (ThumbnailInfo)
    {
        if (TargetDistance + ThumbnailInfo->OrbitZoom < 0)
        {
            ThumbnailInfo->OrbitZoom = -TargetDistance;
        }
    }
    else
    {
        ThumbnailInfo = USceneThumbnailInfo::StaticClass()->GetDefaultObject<USceneThumbnailInfo>();
    }

    OutOrigin = FVector(0, -BoundsZOffset, -BoundsZOffset);
    OutOrbitPitch = ThumbnailInfo->OrbitPitch;
    OutOrbitYaw = 90;
    OutOrbitZoom = TargetDistance + ThumbnailInfo->OrbitZoom;
}
