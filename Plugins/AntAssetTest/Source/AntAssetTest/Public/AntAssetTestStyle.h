#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FAntAssetTestStyle
{
public:

	static void Initialize();
	static void Shutdown();
	static void ReloadTextures();
	static const ISlateStyle& Get();
	static FName GetStyleSetName();

private:
	static TSharedRef< class FSlateStyleSet > Create();
	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};