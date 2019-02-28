// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Mow : ModuleRules
{
	public Mow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	 
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PushForce" });

        //	PrivateDependencyModuleNames.AddRange(new string[] { "PushForce" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
       // PrivateDependencyModuleNames.Add("PushForce");
        PublicDependencyModuleNames.Add("PushForce");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        // The path for the header files
        //    PublicIncludePaths.AddRange(new string[] { "PushForce/Public" });

        // The path for the source files
        // PrivateIncludePaths.AddRange(new string[] { "PushForce/Private" });
    }
}
