// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntTestEdModeModule.h"
#include "AntTestEdModeCommands.h"

#define LOCTEXT_NAMESPACE "AntTestEdModeModule"

void FAntTestEdModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

		FEditorModeRegistry::Get().RegisterMode<FAntTestEdMode>(
			FAntTestEdMode::EM_AntTestEdModeId,
			LOCTEXT("AntTestEdMode", "AntTestEdMode"),
			FSlateIcon(),
			true, 500);
}

void FAntTestEdModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FEditorModeRegistry::Get().UnregisterMode(FAntTestEdMode::EM_AntTestEdModeId);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAntTestEdModeModule, AntTestEdMode)