// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AntAssetTest : ModuleRules
{
	public AntAssetTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Projects",
				"InputCore",
				"EditorFramework",
				"EditorStyle",
				"UnrealEd",
				"ToolMenus",
				"Engine",
				"Slate",
				"SlateCore",
                "AdvancedPreviewScene",
                "RenderCore",
                "RHI",
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		OptimizeCode = CodeOptimization.Never;
	}
}
