#include <Windows.h>
#include <TlHelp32.h>

extern "C" // Allows 'printf' without need for standard lib include
{
int printf(const char *format, ...);
}

bool TerminateSecondInstance(const wchar_t* processName) {
    bool foundFirstInstance = false;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            // Converts the process name to wide char string
            wchar_t wProcessName[MAX_PATH];
            if (MultiByteToWideChar(CP_ACP, 0, pe32.szExeFile, -1, wProcessName, MAX_PATH) > 0) {
                if (wcscmp(wProcessName, processName) == 0) {
                    if (foundFirstInstance) {
                        // Terminate the second instance
                        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                        if (hProcess != nullptr) {
                            TerminateProcess(hProcess, 0);
                            CloseHandle(hProcess);
                            CloseHandle(hSnapshot);
                            return true; // Terminated the second instance (successful termanation)
                        }
                    }
                    foundFirstInstance = true;
                }
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return false; // Second instance not found or couldn't be terminated
}

bool IsProcessRunning(const wchar_t* gameName) { // Could be used in a continuous loop (check if game is opened.)
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            // Convert pe32.szExeFile to a wchar_t* and then compare
            wchar_t wideName[MAX_PATH];
            MultiByteToWideChar(CP_ACP, 0, pe32.szExeFile, -1, wideName, MAX_PATH);
            
            if (wcscmp(wideName, gameName) == 0) {
                CloseHandle(hSnapshot);
                return true;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return false;
}

int main() {
    const wchar_t* processName = L"PluginLoader.exe"; // Defines Executable ModMenu/Plugin Name
    const wchar_t* gameName = L"ISZ-Win64-Shipping.exe"; // Obv. can be changed to specific Game Name
    TerminateSecondInstance(processName);
    Sleep(100);
    if (IsProcessRunning(processName)) {
        MessageBoxW(NULL, L"The ModMenu/Plugin/Cheat was Loaded Successfully.", L"Cracko298's Super Secret ModMenu", MB_OK | MB_ICONINFORMATION); // Passes check, opens Message Diag
    }
    else {
        MessageBoxW(NULL, L"The ModMenu/Plugin/Cheat was **NOT** Loaded (Game Not Present).", L"Cracko298's Super Sad ModMenu", MB_OK | MB_ICONINFORMATION); // Does NOT pass check, opens Message Diag error
    }
    return 0;
}
