#pragma once
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include "stdafx.h"

namespace FunctionHooks
{
	bool DoesFileExist(LPCWSTR path);
	void* __fastcall FindFileInPakFiles_Hook(void* PakFile, void* Filename, void* FileEntry);
	void* __fastcall FindFileInPakFiles_2_Hook(void* PakFile, void* Filename, void** FileEntry);
	__int64 __fastcall IsNonPakFilenameAllowed_Hook(void* thisptr, void* InFilename);
	const wchar_t* GameStart = L"../../../"; // This is at the start of every game path

	//Check if file exists at path
	bool DoesFileExist(LPCWSTR path)
	{
		DWORD dwAttrib = GetFileAttributesW(path);
		return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}


	// FindFileInPakFiles
	typedef void* (*FindFileInPakFiles_ptr)(void* PakFile, void* Filename, void* FileEntry);
	FindFileInPakFiles_ptr FindFileInPakFiles_orig;

	// PakFile::Find hook: this will check for any loose file with the same filename, and if a loose file is found will return false (ie: saying that the .pak doesn't contain it)
	// FindFileInPakFiles 4.12 - 4.27
	void* __fastcall FindFileInPakFiles_Hook(void* PakFile, void* Filename, void* FileEntry)
	{

		const TCHAR* fname = *(TCHAR**)Filename;

		if (wcsstr(fname, GameStart) && DoesFileExist(fname)) {


			return 0; // The file exists outside the PAK and, return false here so the game believes that it doesn't exists in the PAK.
		}

		return FindFileInPakFiles_orig(PakFile, Filename, FileEntry);
	}




	// FindFileInPakFiles 2
	typedef void* (*FindFileInPakFiles_2_ptr)(void* PakFile, void* Filename, void** FileEntry);
	FindFileInPakFiles_2_ptr FindFileInPakFiles_2_orig;


	void* __fastcall FindFileInPakFiles_2_Hook(void* PakFile, void* Filename, void** FileEntry)
	{

		if (FileEntry)
		{
			*FileEntry = nullptr;
		}


		TCHAR* fname = *(TCHAR**)Filename;


		if (Filename && wcsstr(fname, GameStart) && DoesFileExist(fname))
		{

			return 0; // The file exists outside the PAK and, return false here so the game believes that it doesn't exists in the PAK.
		}

		return FindFileInPakFiles_2_orig(PakFile, Filename, FileEntry);
	}





	// ISNONPAKFILENAMEALLOWED
	typedef __int64* (*PakFile__IsNonPakFilenameAllowed_ptr)(void* thisptr, void* InFilename);
	PakFile__IsNonPakFilenameAllowed_ptr PakFile__IsNonPakFilenameAllowed_orig;

	// This allows us to enter the if statement in IFileHandle* FPakPlatformFile::OpenRead where we can then pass the Filename of our loose file so it loads from loose files only if they are available.
	__int64 __fastcall IsNonPakFilenameAllowed_Hook(void* thisptr, void* InFilename)
	{

		return 1;
	}


}

