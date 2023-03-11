#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "ThumbnailHelpers.h"

#include "AntAssetThumbnailRenderer.generated.h"

class FCanvas;
class FRenderTarget;
class USceneThumbnailInfo;

class FAntAssetThumbnailScene : public FStaticMeshThumbnailScene
{
public:
	virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;
	FBoxSphereBounds Bounds;
	UStaticMesh* StaticMesh;
};

UCLASS(config = Editor, MinimalAPI)
class UAntAssetThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()

	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	virtual void BeginDestroy() override;

private:
	class FAntAssetThumbnailScene* ThumbnailScene;

};

