// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrontendUIEditorTarget : TargetRules
{
	public FrontendUIEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("FrontendUI");
	}
}