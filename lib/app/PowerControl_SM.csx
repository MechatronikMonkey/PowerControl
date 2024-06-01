#!/usr/bin/env dotnet-script
// If you have any questions about this file, check out https://github.com/StateSmith/tutorial-2
#r "nuget: StateSmith, 0.9.14-alpha"

using StateSmith.Common;
using StateSmith.Input.Expansions;
using StateSmith.Output.UserConfig;
using StateSmith.Runner;

// See https://github.com/StateSmith/tutorial-2/tree/main/lesson-1
SmRunner runner = new(diagramPath: "PowerControl_SM.drawio.svg", new MyRenderConfig(), transpilerId: TranspilerId.C99);
runner.Run();

// See https://github.com/StateSmith/tutorial-2/tree/main/lesson-2/ (basics)
// See https://github.com/StateSmith/tutorial-2/tree/main/lesson-5/ (language specific options)
public class MyRenderConfig : IRenderConfigC
{
    // NOTE!!! Idiomatic C++ code generation is coming. This will improve.
    // See https://github.com/StateSmith/StateSmith/issues/126
    string IRenderConfigC.CFileExtension => ".cpp"; // the generated StateSmith C code is also valid C++ code
    string IRenderConfigC.HFileExtension => ".h";   // could also be .hh, .hpp or whatever you like

    string IRenderConfig.FileTop => """
        // Whatever you put in the IRenderConfig.FileTop section ends up at the top of the generated file(s).
        """;

    string IRenderConfig.AutoExpandedVars => """
        int auto_expanded_user_example_var;
        """;

    string IRenderConfig.VariableDeclarations => """
        int non_expanded_user_example_var;
        """;

    string IRenderConfigC.HFileTop => """
        // user IRenderConfigC.HFileTop: whatever you want to put in here.
        """;

    string IRenderConfigC.CFileTop => """
        // user IRenderConfigC.CFileTop: whatever you want to put in here.
        //#include <stdio.h> // or whatever you need
        """;

    string IRenderConfigC.HFileIncludes => """
        // user IRenderConfigC.HFileIncludes: whatever you want to put in here.
        """;

    string IRenderConfigC.CFileIncludes => """
        // user IRenderConfigC.CFileIncludes: whatever you want to put in here.
        """;

    // Optional: customize how enumerations are declared so that gcc will use the smallest possible int type instead of a full int.
    // string IRenderConfigC.CEnumDeclarer => "typedef enum __attribute__ ((packed)) {enumName}";

    // See https://github.com/StateSmith/tutorial-2/tree/main/lesson-3
    public class MyExpansions : UserExpansionScriptBase
    {
        // See https://github.com/StateSmith/tutorial-2/tree/main/lesson-4 for timing expansions
    }
}
