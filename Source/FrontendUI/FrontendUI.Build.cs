// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrontendUI : ModuleRules
{
	public FrontendUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "UMG", "CommonUI",
			"CommonUIEditor", "DeveloperSettings"
		]);

		PrivateDependencyModuleNames.AddRange([]);
}
}