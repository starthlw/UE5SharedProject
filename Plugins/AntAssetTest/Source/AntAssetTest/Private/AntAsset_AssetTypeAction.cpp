#include "AntAsset_AssetTypeAction.h"
#include "AntAsset.h"
#include "AntAssetTestModule.h"
#include "AntAssetEditor.h"

#define LOCTEXT_NAMESPACE "AntAsset"

FText FAntAsset_AssetTypeAction::GetName() const
{
    return NSLOCTEXT("AssetTypeActions", "FAntAsset_AssetTypeAction", "AntAssetTest");
}

UClass* FAntAsset_AssetTypeAction::GetSupportedClass() const
{
    return UAntAsset::StaticClass();
}

uint32 FAntAsset_AssetTypeAction::GetCategories()
{
    return FAntAssetTestModule::GetAssetCategory();
}

void FAntAsset_AssetTypeAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
    EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
    for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
    {
        if (auto Object = Cast<UAntAsset>(*ObjIt))
        {
            FAntAssetEditorToolkit::CreateEditor(Mode, Mode == EToolkitMode::WorldCentric ? EditWithinLevelEditor : TSharedPtr<IToolkitHost>(), Object);
        }
    }
}
#undef LOCTEXT_NAMESPACE