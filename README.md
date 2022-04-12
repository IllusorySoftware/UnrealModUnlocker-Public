# UnrealModUnlocker-Public 1.0.0

UnrealModUnlocker Public and UnrealModUnlocker Basic are NOT the same codebase.
UnrealModUnlocker Public ONLY contains code for the loose file loading part of the UMU Project.
Since UnrealModUnlocker Public now supports ALL version of Unreal Engine 4 (compiled with the standard compiler settings in visual studio),
it is now considered FINAL and version 1.0.0.

Unlocks loading of Third Party Unreal Engine 4 loose files for 90-95% of UE4 games.
This software is for unlocking loading of loose file packages (.uasset | .ubulk | .uexp | .umap and any other file you could normally find inside the PAK archives).
Any file already in a PAK archive has a virtual path. (You can find filetype and filepath with UMODEL or FMODEL)
Recreate the same filetype and filepath in an Unreal Engine 4 project.
Cook files in UE4.
Copy the "modded" file with the proper file path structure into the correct place in the game folders.
Make sure to have the UnrealModUnlocker installed in the Game/ProjectName/Binaries/Win64/ folder.
Run game!
Done!

## 1.0.0 Changes:

Added support for 4.0 | 4.1 | 4.2 | 4.3 | 4.4 | 4.5 | 4.6 and 4.7 and can now confirm this tool has 100% support for Unreal Engine 4
games as long as they are compiled with the standard visual studio compiler settings.

-Added support for a different compiler output for 4.16 that was found in Life Is Strange 2.

-Added support for a different compiler output for 4.25 that was found in Kena.

-Added support for a different compiler output for 4.18 that was found in Biomutant.

I will add further compatibility for non-standard compiler settings and non-standard compilers to keep this
updated with the Unreal Mod Unlocker Basic and pro project as people report issues with comaptibility to me.


## How to use:
**Step 1:** Build the source for 64-Bit Release

**Step 2:** Rename output DLL to dxgi.dll

**Step 3:** Put dxgi.dll in "/Game/ProjectName/Binaries/Win64/"

**Step 4:** Run Game with mods applied

**Step 5:** Profit!



## Compatibility:

Engine  | Version | Supported Architecture |  Compatibility
------------- | ------------- | ------------- | -------------
Unreal Engine | 4.0  | x64  | Supported
Unreal Engine | 4.1  | x64  | Supported
Unreal Engine | 4.2  | x64  | Supported
Unreal Engine | 4.3  | x64  | Supported
Unreal Engine | 4.4  | x64  | Supported
Unreal Engine | 4.5  | x64  | Supported
Unreal Engine | 4.6  | x64  | Supported
Unreal Engine | 4.7  | x64  | Supported
Unreal Engine | 4.8  | x64  | Supported
Unreal Engine | 4.9  | x64  | Supported
Unreal Engine | 4.10  | x64  | Supported
Unreal Engine | 4.11  | x64  | Supported
Unreal Engine | 4.12  | x64  | Supported
Unreal Engine | 4.13  | x64  | Supported
Unreal Engine | 4.14  | x64  | Supported
Unreal Engine | 4.15  | x64  | Supported
Unreal Engine | 4.16  | x64  | Supported
Unreal Engine | 4.17  | x64  | Supported
Unreal Engine | 4.18  | x64  | Supported
Unreal Engine | 4.19  | x64  | Supported
Unreal Engine | 4.20  | x64  | Supported
Unreal Engine | 4.21  | x64  | Supported
Unreal Engine | 4.22  | x64  | Supported
Unreal Engine | 4.23  | x64  | Supported
Unreal Engine | 4.24  | x64  | Supported
Unreal Engine | 4.25  | x64  | Supported
Unreal Engine | 4.26  | x64  | Supported
Unreal Engine | 4.27  | x64  | Supported

## How to add support for YOUR game:
Tutorial to help you add support for your game: https://www.youtube.com/watch?v=Uf3cArpU6Xk



### Credits:
Special Thanks to emoose for DQXIHook and dga711 for ezpz, which made this possible.


## /GHFear and Genesis @ IllusorySoftware
