// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FIrstGame : ModuleRules
{
	public FIrstGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "NavigationSystem", "AIModule" });
	}
}
