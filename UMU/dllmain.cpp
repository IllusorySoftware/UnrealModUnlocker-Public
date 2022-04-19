// UMU 2022 (An Unreal Engine 4 Third Party Content Creation Unlocker)
// Created By GHFear @ Illusory Software


// INCLUDES ------------------------>

#include "stdafx.h"
#include <stdint.h>
#include <stdio.h>

#include "MinHook/MinHook.h"
#include "proxy.h"
#include "FunctionSignatures.h"
#include "FunctionHooks.h"

#include <shellapi.h>


//------------------------ END OF INCLUDES


// Setup for the dxgi Proxy
EXTERN_C IMAGE_DOS_HEADER __ImageBase; // We might need this some day. Don't remove.
HMODULE ourModule = 0; // Declare our "extern HMODULE ourModule" from proxy.cpp inside dllmain, so we can pass hModule to Proxy_Attach();


//Function Defs -------------------->
DWORD WINAPI RevertToStock(LPVOID lpParam);
void Hooks();
void Initiate_Hooks();

//------------------------ END OF Function Defs



//Set our important Global Vars ------>
char* exe_base = nullptr;

//------------------------ END OF Global Vars

//Start routine
BOOL APIENTRY DllMain(HMODULE hModule, int ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		ourModule = hModule;
		Proxy_Attach();

		Initiate_Hooks();

	}
	if (ul_reason_for_call == DLL_PROCESS_DETACH)
		Proxy_Detach();

	return TRUE;
}


//Show an error message and start the game without hooking.
DWORD WINAPI RevertToStock(LPVOID lpParam)
{
	
	const int result = MessageBox(NULL, L"Warning! \n\nThe game could be using SteamStub DRM (Use Steamless and / or Goldberg Emulator to get around this) \nor The mod unlocker does not support this title or doesn't support this engine version yet! \n\nClick YES to join our discord so we can quickly add support for your game! (Contact GHFear) \n\nClick NO if you want to play the game vanilla style! \n\nClick CANCEL to Quit the game!", L"Team Illusory", MB_YESNOCANCEL | MB_SYSTEMMODAL);

	switch (result)
	{
	case IDYES:
		ShellExecute(0, 0, L"https://discord.com/invite/Mt3qzgN", 0, 0, SW_SHOW);
		break;
	case IDNO:
		break;
	case IDCANCEL:
		abort();
		break;
	}
	
	return 0;

}


void Hooks()
{

	FunctionSignatures function_sigs; //Create sigscans object

	const size_t addr_FindFileInPakFiles = function_sigs.Get_addr_Pakfile__Find(); // address of FindFileInPakFiles
	char* FindFileInPakFiles = exe_base + addr_FindFileInPakFiles;

	// FPakPlatformFile::IsNonPakFilenameAllowed(FString const &)
	const size_t addr_IsNonPakFilenameAllowed = function_sigs.Get_IsNonPakFileNameAllowedAddr(); // address of IsNonPakFilenameAllowed;
	char* IsNonPakFilenameAllowed = exe_base + addr_IsNonPakFilenameAllowed; // exe_base + addr_IsNonPakFilenameAllowed;

	//BASIC
	if (addr_FindFileInPakFiles != -1 && addr_IsNonPakFilenameAllowed != -1 && function_sigs.Find_File_In_PakFile_Version == 1 && function_sigs.bNoIsNonPakFileNameAllowed == false)
	{
		if (MH_CreateHook((void*)FindFileInPakFiles, FunctionHooks::FindFileInPakFiles_Hook, (LPVOID*)&FunctionHooks::FindFileInPakFiles_orig) == MH_OK)// Create our PakFile__Find_hook with minhook
		{
			MH_EnableHook((void*)FindFileInPakFiles); // Enable our PakFile__Find_hook
		}


		if (MH_CreateHook((void*)IsNonPakFilenameAllowed, FunctionHooks::IsNonPakFilenameAllowed_Hook, (LPVOID*)&FunctionHooks::PakFile__IsNonPakFilenameAllowed_orig) == MH_OK)// Create our IsNonPakFilenameAllowed_hook with minhook
		{
			MH_EnableHook((void*)IsNonPakFilenameAllowed); // Enable our IsNonPakFilenameAllowed_hook
		}
	}
	else if (addr_FindFileInPakFiles != -1 && addr_IsNonPakFilenameAllowed != -1 && function_sigs.Find_File_In_PakFile_Version == 2 && function_sigs.bNoIsNonPakFileNameAllowed == false)
	{
		if (MH_CreateHook((void*)FindFileInPakFiles, FunctionHooks::FindFileInPakFiles_2_Hook, (LPVOID*)&FunctionHooks::FindFileInPakFiles_2_orig) == MH_OK)// Create our PakFile__Find_2_hook with minhook
		{
			MH_EnableHook((void*)FindFileInPakFiles); // Enable our PakFile__Find_2_hook
		}


		if (MH_CreateHook((void*)IsNonPakFilenameAllowed, FunctionHooks::IsNonPakFilenameAllowed_Hook, (LPVOID*)&FunctionHooks::PakFile__IsNonPakFilenameAllowed_orig) == MH_OK)// Create our IsNonPakFilenameAllowed_hook with minhook
		{
			MH_EnableHook((void*)IsNonPakFilenameAllowed); // Enable our IsNonPakFilenameAllowed_hook
		}
	}
	else if (addr_IsNonPakFilenameAllowed == -1 && addr_FindFileInPakFiles != -1 && function_sigs.Find_File_In_PakFile_Version == 1 && function_sigs.bNoIsNonPakFileNameAllowed == true)
	{
		if (MH_CreateHook((void*)FindFileInPakFiles, FunctionHooks::FindFileInPakFiles_Hook, (LPVOID*)&FunctionHooks::FindFileInPakFiles_orig) == MH_OK)// Create our PakFile__Find_hook with minhook
		{
			MH_EnableHook((void*)FindFileInPakFiles); // Enable our PakFile__Find_hook
		}
	}
	else if (addr_IsNonPakFilenameAllowed == -1 && addr_FindFileInPakFiles != -1 && function_sigs.Find_File_In_PakFile_Version == 2 && function_sigs.bNoIsNonPakFileNameAllowed == true)
	{
		if (MH_CreateHook((void*)FindFileInPakFiles, FunctionHooks::FindFileInPakFiles_2_Hook, (LPVOID*)&FunctionHooks::FindFileInPakFiles_2_orig) == MH_OK)// Create our PakFile__Find_2_hook with minhook
		{
			MH_EnableHook((void*)FindFileInPakFiles); // Enable our PakFile__Find_2_hook
		}
	}
	else
	{
		CreateThread(NULL, 0, &RevertToStock, NULL, 0, NULL); // Show a revert to stock message and start the game without hooking anything.
	}

}


void Initiate_Hooks()
{
	exe_base = (char*)GetModuleHandleA(NULL); //Get exe base

	if (!exe_base)
	{
		return;
	}

	MH_Initialize(); // Initialize MinHook
	Hooks(); //Run HookPakFile function
}


