#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AntAssetTestStyle.h"

class FAntAssetEditorCommands : public TCommands<FAntAssetEditorCommands>
{
public:

	FAntAssetEditorCommands()
		: TCommands<FAntAssetEditorCommands>(TEXT("AntAssetTest"), NSLOCTEXT("Contexts", "AntAssetTest", "AntAssetTest Plugin"), NAME_None, FAntAssetTestStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;
};