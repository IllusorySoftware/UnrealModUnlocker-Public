#include <windows.h>
#include <string>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static bool initialized = false;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!initialized)
        {
            initialized = true;

            HANDLE hMutex = CreateMutexW(NULL, TRUE, L"PluginLoaderW");
            if (GetLastError() == ERROR_ALREADY_EXISTS)
            {
                CloseHandle(hMutex);
                return FALSE;
            }

            Sleep(2000);
            wchar_t dllPath[MAX_PATH];
            GetModuleFileNameW(hModule, dllPath, MAX_PATH);

            wcsrchr(dllPath, L'\\')[1] = L'\0';

            wchar_t batchFilePath[MAX_PATH];
            wcscpy_s(batchFilePath, dllPath);
            wcscat_s(batchFilePath, L"ModMenuExample.exe");

            _wsystem((L"cmd.exe /C start \"\" \"" + std::wstring(batchFilePath) + L"\"").c_str());

            CloseHandle(hMutex);
            return FALSE;
        }
        break;
    case DLL_PROCESS_DETACH:
        return FALSE;
    }

    return FALSE;
}
