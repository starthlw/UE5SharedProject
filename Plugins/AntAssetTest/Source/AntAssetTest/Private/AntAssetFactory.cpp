// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntAssetFactory.h"
#include "AssetTypeCategories.h"
#include "AntAsset.h"

#define LOCTEXT_NAMESPACE "AntAssetFactory"

UAntAssetFactory::UAntAssetFactory()
{
    bCreateNew = true;
    bEditAfterNew = true;
    SupportedClass = UAntAsset::StaticClass();
}

UObject* UAntAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UAntAsset* NewAsset = NewObject<UAntAsset>(InParent, Class, Name, Flags | RF_Transactional);
    return NewAsset;
}

FText UAntAssetFactory::GetToolTip() const
{
    return LOCTEXT("AntAssetTooltip", "Creates ant asset");
}

#undef LOCTEXT_NAMESPACE