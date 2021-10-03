#include <iostream>
#include <synchapi.h>
#include "windows.h"
#include <dirent.h>

std::string current_working_directory()
{
    char* cwd = _getcwd( 0, 0 ) ;
    std::string working_directory(cwd) ;
    std::free(cwd) ;
    return working_directory ;
}

int main() {
    std::string path = current_working_directory();

    std::string  OS03_02_1_str = path + "\\OS03_02_1.exe";
    std::string  OS03_02_2_str = path + "\\OS03_02_2.exe";

    LPCSTR OS03_02_1 = OS03_02_1_str.c_str();
    LPCSTR OS03_02_2 = OS03_02_2_str.c_str();

    STARTUPINFO cif1;
    STARTUPINFO cif2;
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;

    ZeroMemory(&cif1, sizeof(STARTUPINFO)); cif1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&cif2, sizeof(STARTUPINFO)); cif2.cb = sizeof(STARTUPINFO);

    if(CreateProcess(OS03_02_1,  NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &cif1, &pi1)){
            std::cout << "CREATED PROCESS OS03_02_1" << std::endl;
    } else{
        std::cout << "NOT CREATED PROCESS OS03_02_1" << std::endl;
    }

    if(CreateProcess(OS03_02_2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &cif2, &pi2)){
        std::cout << "CREATED PROCESS OS03_02_2" << std::endl;
    } else{
        std::cout << "NOT CREATED PROCESS OS03_02_" << std::endl;
    }

    for(int i = 0; i < 100; i++ ){
        std::cout << "OS03_03, " << "PID: " << GetCurrentProcessId() << std::endl;
        Sleep(1000);
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
    return 0;
}


