#include <iostream>
#include "windows.h"
#include <bitset>

int main(int argc, char* argv[]) {
    DWORD mask;
    DWORD priority_1;
    DWORD priority_2;
    char *end;

    try {
        if (argc > 3) {
            mask = strtol(argv[1], &end, 10);
            priority_1 = strtol(argv[2], &end, 10);
            priority_2 = strtol(argv[3], &end, 10);
        } else {
            throw "not exist parameters (mask, priority 1, priority 2)";
        }
    }catch (const char* exception){
        std::cerr << "Error: " << exception << '\n';
        system("pause");
        exit(-1);

    }


    std::wstring  OS05_02_1_str =  L"D:\\GitHub\\OS_SysDev\\Lab5\\Visual Studio\\Lab 5\\Debug\\OS05_02x.exe";
    std::wstring  OS05_02_2_str =  L"D:\\GitHub\\OS_SysDev\\Lab5\\Visual Studio\\Lab 5\\Debug\\OS05_02x.exe";

    LPCWSTR OS05_02_1 = OS05_02_1_str.c_str();
    LPCWSTR OS05_02_2 = OS05_02_2_str.c_str();

    STARTUPINFO cif1;
    STARTUPINFO cif2;
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;
    HANDLE handler = GetCurrentProcess();

    ZeroMemory(&cif1, sizeof(STARTUPINFO)); cif1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&cif2, sizeof(STARTUPINFO)); cif2.cb = sizeof(STARTUPINFO);

    bool success = SetProcessAffinityMask(handler,mask);
    if(success) {
        ULONG_PTR processAffinityMask;
        ULONG_PTR systemAffinityMask;
        success = GetProcessAffinityMask(handler, &processAffinityMask, &systemAffinityMask);
        if(success){
            std::cout << "process mask           " << std::showbase << std::bitset<8>(processAffinityMask) << std::endl;
        }
    }


    if (!CreateProcess(OS05_02_1, nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE | priority_1, nullptr, nullptr, &cif1, &pi1)) {
        std::cout << "NOT CREATED PROCESS OS03_02_1" << std::endl;
    } else {
        std::cout << "CREATED PROCESS OS03_02_1" << std::endl;
    }

    if(CreateProcess(OS05_02_2, nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE | priority_2, nullptr, nullptr, &cif2, &pi2)){
        std::cout << "CREATED PROCESS OS03_02_2" << std::endl;
    } else{
        std::cout << "NOT CREATED PROCESS OS03_02_" << std::endl;
    }
    std::cout << "wait..." << std::endl;

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
    return 0;
}


