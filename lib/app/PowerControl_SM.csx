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
        int initSuccess = 0;
        int pwrWaitON = 0;
        int pwrWaitOFF = 0;
        AppController *parent;
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
        #include "AppController.h"
        """;

    string IRenderConfigC.CFileIncludes => """
        // user IRenderConfigC.CFileIncludes: whatever you want to put in here.
        """;

    // Optional: customize how enumerations are declared so that gcc will use the smallest possible int type instead of a full int.
    // string IRenderConfigC.CEnumDeclarer => "typedef enum __attribute__ ((packed)) {enumName}";

    // See https://github.com/StateSmith/tutorial-2/tree/main/lesson-3
    public class MyExpansions : UserExpansionScriptBase
    {
        public string init_success => VarsPath + "initSuccess";
        public string showErrorScreen() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showMainScreen() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showPwrStatus() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string getInitState() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string pwr => $"sm->vars.parent->{AutoNameCopy()}";
        public string pwrCounter => $"sm->vars.parent->{AutoNameCopy()}";
        public string showNextFull() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string pwrLEDoff() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string pwrLEDon() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string pwrRelaisOn() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string pwrRelaisOff() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string getPwrSetting() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string calcWaitTimes() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string pwrWaitOff => $"sm->vars.parent->{AutoNameCopy()}";
        public string pwrWaitOn => $"sm->vars.parent->{AutoNameCopy()}";
        public string showSetupScreen() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showSetupMsg() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string savePwrSetting() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showNextOff() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showNextAtt() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showPwrCtrlScreen() => $"sm->vars.parent->{AutoNameCopy()}()";
        public string showFullScreen() => $"sm->vars.parent->{AutoNameCopy()}()";
        // See https://github.com/StateSmith/tutorial-2/tree/main/lesson-4 for timing expansions
    }
}
