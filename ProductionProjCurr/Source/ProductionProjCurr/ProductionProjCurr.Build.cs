using UnrealBuildTool;

public class ProductionProjCurr : ModuleRules
{
	public ProductionProjCurr(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "StateTreeModule",
            "GameplayStateTreeModule",
            "UMG",
            "Slate",
            "SlateCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ProductionProjCurr",
			"ProductionProjCurr/Variant_Platforming",
			"ProductionProjCurr/Variant_Combat",
			"ProductionProjCurr/Variant_Combat/AI",
			"ProductionProjCurr/Variant_SideScrolling",
			"ProductionProjCurr/Variant_SideScrolling/Gameplay",
			"ProductionProjCurr/Variant_SideScrolling/AI"
		});

	}
}
