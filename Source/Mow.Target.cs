// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MowTarget : TargetRules
{
	public MowTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Mow" } );

        //PublicDependencyModuleNames.AddRange(new string[] { "PushForce" });
    }
}
