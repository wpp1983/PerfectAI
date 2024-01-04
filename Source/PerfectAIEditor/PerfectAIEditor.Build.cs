using UnrealBuildTool;

public class PerfectAIEditor : ModuleRules
{
    public PerfectAIEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "UnrealEd",
                "AssetDefinition",
                "PerfectAI",
            }
        );
    }
}