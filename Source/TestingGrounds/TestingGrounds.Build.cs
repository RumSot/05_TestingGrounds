// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestingGrounds : ModuleRules
{
	public TestingGrounds(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "NavigationSystem" });     // Post UE_4.20.1 "NavigationSystem" is needed to prevent linker errors when we use ANavMeshBoundsVolume
	}
}
