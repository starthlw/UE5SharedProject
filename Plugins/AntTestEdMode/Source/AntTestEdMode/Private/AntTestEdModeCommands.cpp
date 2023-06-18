// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntTestEdModeCommands.h"
#include "AntTestEdMode.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "AntTestEdModeCommands"

FAntTestEdModeCommands::FAntTestEdModeCommands()
	: TCommands<FAntTestEdModeCommands>("AntTestEdMode",
		NSLOCTEXT("AntTestEdMode", "AntTestEdModeCommands", "AntTestEdMode"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FAntTestEdModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FAntTestEdModeCommands::GetCommands()
{
	return FAntTestEdModeCommands::Get().Commands;
}

#undef LOCTEXT_NAMESPACE
