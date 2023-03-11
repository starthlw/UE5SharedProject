#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "AntAsset.generated.h"

struct ViewportObject
{
    TObjectPtr<UStaticMeshComponent> Component;
    FTransform Transform;
    ViewportObject(TObjectPtr<UStaticMeshComponent> Component, FTransform Transform) : Component(Component), Transform(Transform) {}
};

UCLASS(BlueprintType, NotBlueprintable, AutoExpandCategories = "AntAsset")
class ANTASSETTEST_API UAntAsset : public UObject
{
    GENERATED_UCLASS_BODY()
    DECLARE_DELEGATE(FPostEditCallback)

public:
    virtual void BeginDestroy() override;
#if WITH_EDITOR
    virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
    virtual void PostLoad() override;
    virtual void PreEditUndo() override;
    virtual void PostEditUndo() override;
    virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

    void AntAssetModify();

public:
    UPROPERTY(Category = Procedural, EditAnywhere, meta = (Subcategory = "Growth", XAxisName = "Normalized Age", YAxisName = "Scale Factor"))
    FRuntimeFloatCurve ScaleCurve;

    UPROPERTY(Category = Procedural, EditAnywhere, meta = (Subcategory = "Growth"))
    TObjectPtr<UStaticMesh> Mesh;

    UPROPERTY(Category = Procedural, EditAnywhere, meta = (Subcategory = "Growth"))
    uint32 Num;

    FPostEditCallback PostEditCallback;

    TArray<ViewportObject> ViewportComponents;

};
