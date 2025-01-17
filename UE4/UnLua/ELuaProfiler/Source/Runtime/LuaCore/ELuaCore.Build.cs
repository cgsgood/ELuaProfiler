// The MIT License (MIT)

// Copyright 2020 HankShu inkiu0@gmail.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

using UnrealBuildTool;
using System.IO;

public class ELuaCore : ModuleRules
{
    public ELuaCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        // enable exception
        bEnableExceptions = true;
        IWYUSupport = IWYUSupport.None;
        bEnableUndefinedIdentifierWarnings = false;
#if UE_4_21_OR_LATER
        PublicDefinitions.Add("ENABLE_ELUAPROFILER");
#else
        Definitions.Add("ENABLE_ELUAPROFILER");
#endif


        PublicIncludePaths.AddRange(
            new string []
            {
                //"Runtime/LuaCore/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "Runtime/LuaCore/Private"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "InputCore",
                "Networking",
                "Sockets",
                "Lua",
                "UnLua",
                // ... add private dependencies that you statically link with here ...	
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Lua",
                "UnLua",
                // ... add other public dependencies that you statically link with here ...
            }
        );
    }
}
