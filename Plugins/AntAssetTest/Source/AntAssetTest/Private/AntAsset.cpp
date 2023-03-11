#include "AntAsset.h"


UAntAsset::UAntAsset(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    auto Curve = ScaleCurve.GetRichCurve();
    Curve->AddKey(0.f, 1.f);
    Curve->AddKey(1.f, 1.f);
}


void UAntAsset::BeginDestroy()
{
    Super::BeginDestroy();
	
}

#if WITH_EDITOR
void UAntAsset::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
    Super::PostDuplicate(DuplicateMode);

}

void UAntAsset::PostLoad()
{
    Super::PostLoad();

}

void UAntAsset::PreEditUndo()
{
    Super::PreEditUndo();

}

void UAntAsset::PostEditUndo()
{
    Super::PostEditUndo();

}

void UAntAsset::PreEditChange(FProperty* PropertyAboutToChange)
{
    Super::PreEditChange(PropertyAboutToChange);

}

void UAntAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    //OnUpdateWavesAssetData.Broadcast(this, PropertyChangedEvent.ChangeType);
    AntAssetModify();
}

void UAntAsset::AntAssetModify()
{
    Modify();
    PostEditCallback.ExecuteIfBound();
}

#endif // WITH_EDITOR


