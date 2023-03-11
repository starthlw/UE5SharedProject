// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntAssetTestStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAntAssetTestStyle::StyleInstance = nullptr;

void FAntAssetTestStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAntAssetTestStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAntAssetTestStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AntAssetTestStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAntAssetTestStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AntAssetTestStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AntAssetTest")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AntAssetTest.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FAntAssetTestStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAntAssetTestStyle::Get()
{
	return *StyleInstance;
}
