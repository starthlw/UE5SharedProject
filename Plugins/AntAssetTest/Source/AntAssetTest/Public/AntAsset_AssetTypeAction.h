#pragma once

#include "AssetTypeActions_Base.h"

class FAntAsset_AssetTypeAction : public FAssetTypeActions_Base
{
public:
    virtual FText GetName() const override;
    virtual FColor GetTypeColor() const override { return FColor(0, 85, 200); }
    virtual UClass* GetSupportedClass() const override;
    virtual uint32 GetCategories() override;
    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
};