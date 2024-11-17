// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheExiledKnight : ModuleRules
{
	public TheExiledKnight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
        { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
        "AIModule", "GameplayTasks", "MovieScene", "LevelSequence", "NavigationSystem", "GameplayTags", "UMG", "Niagara"});

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PrivateIncludePaths.Add("TheExiledKnight");
    }
}
