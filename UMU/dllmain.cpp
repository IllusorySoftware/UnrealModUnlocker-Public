// UMU 2021 (An Unreal Engine 4 Third Party Content Creation Unlocker)
// Originally made for DQXI (emoose) and Session (dga711), but now works with 90% of Unreal Engine 4 PC titles (GHFear).
// Sig scanning part of the project can be found in util.h and SigScans.h if you want to make changes or add more sigs.


// INCLUDES

#include "stdafx.h"
#include <stdint.h>
#include <stdio.h>

#include "MinHook/MinHook.h"
#include "proxy.h"
#include "SigScans.h"
#include "global.h"
#include "util.h"

#include <sstream>
#include <string>


//------------------------ END OF INCLUDES


// Setup for the dxgi Proxy
EXTERN_C IMAGE_DOS_HEADER __ImageBase; // We might need this some day. Don't remove.
HMODULE ourModule = 0; // Declare our "extern HMODULE ourModule" from proxy.cpp inside dllmain, so we can pass hModule to Proxy_Attach();


//Function Defs
bool DoesFileExist(LPCWSTR path);
DWORD WINAPI RevertToStock(LPVOID lpParam);
void* __fastcall FindFileInPakFiles_Hook(void* thisptr, void* Filename, void* OutEntry);
void* __fastcall FindFileInPakFiles_DQXIS_Hook(void* Paks, TCHAR* Filename, void** OutPakFile);
__int64 __fastcall IsNonPakFilenameAllowed_Hook(void* thisptr, void* InFilename);
void Hook_PakFile();
void Init_Hooks();

//------------------------ END OF Function Defs

//Start routine
BOOL APIENTRY DllMain(HMODULE hModule, int ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		ourModule = hModule;
		Proxy_Attach();

		Init_Hooks();

	}
	if (ul_reason_for_call == DLL_PROCESS_DETACH)
		Proxy_Detach();

	return TRUE;
}



//Check if file exists at path
bool DoesFileExist(LPCWSTR path)
{
	DWORD dwAttrib = GetFileAttributesW(path);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


//Show an error message and start the game without hooking.
DWORD WINAPI RevertToStock(LPVOID lpParam)
{

	MessageBox(nullptr, TEXT("Warning! The mod unlocker does not support this title or doesn't support this engine version yet! The game will now run vanilla style."), TEXT("Team Illusory"), MB_SYSTEMMODAL);

	return 0;

}


// Set our important addresses, offsets and other values.
char* exe_base = nullptr;
const wchar_t* GameStart = L"../../../"; // This is at the start of every game path


// FindFileInPakFiles
typedef void* (*FindFileInPakFiles_ptr)(void* PakFile, void* Filename, void* FileEntry);
FindFileInPakFiles_ptr FindFileInPakFiles_orig;

// PakFile::Find hook: this will check for any loose file with the same filename, and if a loose file is found will return false (ie: saying that the .pak doesn't contain it)

void* __fastcall FindFileInPakFiles_Hook(void* PakFile, void* Filename, void* FileEntry)
{

	const TCHAR* fname = *(TCHAR**)Filename;

	if (wcsstr(fname, GameStart) && DoesFileExist(fname)) {


		return 0; // The file exists outside the PAK and, return false here so the game believes that it doesn't exists in the PAK.
	}

	return FindFileInPakFiles_orig(PakFile, Filename, FileEntry);
}





// FindFileInPakFiles DQXI S
typedef void* (*FindFileInPakFiles_DQXIS_ptr)(void* PakFile, void* Filename, void** FileEntry);
FindFileInPakFiles_DQXIS_ptr FindFileInPakFiles_DQXIS_orig;

void* __fastcall FindFileInPakFiles_DQXIS_Hook(void* PakFile, TCHAR* Filename, void** FileEntry)
{

	if (FileEntry)
	{
		*FileEntry = nullptr;
	}


	if (Filename && wcsstr(Filename, GameStart) && DoesFileExist(Filename))
	{
		return 0; // The file exists outside the PAK and, return false here so the game believes that it doesn't exists in the PAK.
	}

	return FindFileInPakFiles_DQXIS_orig(PakFile, Filename, FileEntry);
}





// ISNONPAKFILENAMEALLOWED
typedef __int64* (*PakFile__IsNonPakFilenameAllowed_ptr)(void* thisptr, void* InFilename);
PakFile__IsNonPakFilenameAllowed_ptr PakFile__IsNonPakFilenameAllowed_orig;

// This allows us to enter the if statement in IFileHandle* FPakPlatformFile::OpenRead where we can then pass the Filename of our loose file so it loads from loose files only if they are available.
__int64 __fastcall IsNonPakFilenameAllowed_Hook(void* thisptr, void* InFilename)
{

	return 1;
}



void Hook_PakFile()
{

	const size_t addr_FindFileInPakFiles = SigScans::Get_addr_Pakfile__Find(); // address of FindFileInPakFiles
	char* FindFileInPakFiles = exe_base + addr_FindFileInPakFiles;

	// FPakPlatformFile::IsNonPakFilenameAllowed(FString const &)
	const size_t addr_IsNonPakFilenameAllowed = SigScans::Get_IsNonPakFileNameAllowedAddr(); // address of IsNonPakFilenameAllowed;
	char* IsNonPakFilenameAllowed = exe_base + addr_IsNonPakFilenameAllowed; // exe_base + addr_IsNonPakFilenameAllowed;

	if (addr_FindFileInPakFiles != -1 && addr_IsNonPakFilenameAllowed != -1 && SigScans::bSpecialCaseGame == false)
	{
		MH_CreateHook((void*)FindFileInPakFiles, FindFileInPakFiles_Hook, (LPVOID*)&FindFileInPakFiles_orig); // Create our PakFile__Find_hook with minhook
		MH_EnableHook((void*)FindFileInPakFiles); // Enable our PakFile__Find_hook

		MH_CreateHook((void*)IsNonPakFilenameAllowed, IsNonPakFilenameAllowed_Hook, (LPVOID*)&PakFile__IsNonPakFilenameAllowed_orig); // Create our IsNonPakFilenameAllowed_hook with minhook
		MH_EnableHook((void*)IsNonPakFilenameAllowed); // Enable our IsNonPakFilenameAllowed_hook

	}
	else if (addr_FindFileInPakFiles != -1 && addr_IsNonPakFilenameAllowed != -1 && SigScans::bSpecialCaseGame == true)
	{
		//List games that don't follow the norm here.
		if (SigScans::DQXI_S == true)
		{
			MH_CreateHook((void*)FindFileInPakFiles, FindFileInPakFiles_DQXIS_Hook, (LPVOID*)&FindFileInPakFiles_DQXIS_orig); // Create our PakFile__Find_DQXIS_hook with minhook
			MH_EnableHook((void*)FindFileInPakFiles); // Enable our PakFile__Find_DQXIS_hook

			MH_CreateHook((void*)IsNonPakFilenameAllowed, IsNonPakFilenameAllowed_Hook, (LPVOID*)&PakFile__IsNonPakFilenameAllowed_orig); // Create our IsNonPakFilenameAllowed_hook with minhook
			MH_EnableHook((void*)IsNonPakFilenameAllowed); // Enable our IsNonPakFilenameAllowed_hook
		}
		else
		{
			CreateThread(NULL, 0, &RevertToStock, NULL, 0, NULL); // Show a revert to stock message and start the game without hooking anything.
		}
	}
	else
	{
		CreateThread(NULL, 0, &RevertToStock, NULL, 0, NULL); // Show a revert to stock message and start the game without hooking anything.
	}

}


void Init_Hooks()
{
	exe_base = (char*)GetModuleHandleA(NULL); //Get exe base

	if (!exe_base)
	{
		return;
	}

	MH_Initialize(); // Initialize MinHook
	Hook_PakFile(); //Run HookPakFile function

	DWORD dwOld;


}


