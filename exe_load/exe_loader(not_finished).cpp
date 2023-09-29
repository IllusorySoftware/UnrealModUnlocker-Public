#include <include\windows.h>

extern "C"
{
int printf(const char *format, ...);
}

void LoadISZPlugin() {
    printf("Plugin Has Been Loaded.\n");
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory); // Current Path

    std::string configFile = currentDirectory;
    configFile += "\\isz_plg.config"; // Set 'isz_plg.config' as config file (required)

    // Open the config file
    HANDLE hFile = CreateFile(configFile.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) { // If file doesn't exist
        return;
    }

    char buffer[1024];
    DWORD bytesRead;
    int lineCount = 0;

    while (lineCount < 2) {
        if (!ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL)) {
            CloseHandle(hFile);
            return;
        }

        if (bytesRead == 0) { // Error Handle (eof)
            CloseHandle(hFile);
            return;
        }

        for (DWORD i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                lineCount++;
                if (lineCount == 2) {
                    buffer[i] = '\0';
                    break;
                }
            }
        }
    }

    CloseHandle(hFile);

    char* secondLine = strchr(buffer, '\0') + 1; // Path to EXE (To Execute)

    while (1==1){
        printf("Example Code. Will put more here.");
        printf(secondLine);
        Sleep(100);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            LoadISZPlugin();
            break;
        case DLL_PROCESS_DETACH:
            break;
        default:
            break;
    }
    return TRUE;
}
