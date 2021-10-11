#include <Windows.h>
#include <Tlhelp32.h>
#include <iostream>
#define FIRST_ROW 35
#define SECOND_ROW 20
#define THIRD_ROW 20
#define SEPARATOR " | "
#include <string>




int main() {
    DWORD pid = GetCurrentProcessId();
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);

    PROCESSENTRY32 peProcessEntry;
    peProcessEntry.dwSize = sizeof (PROCESSENTRY32);

    std::wcout << L"Current PID = " << pid << std::endl << L"-----------------------------------" << std::endl;
    try {
        if (!Process32First(snap, &peProcessEntry)) throw L"Process32First";
        std::wcout.setf(std::ios::left);
        std::wcout.width(FIRST_ROW);  std::wcout << L"Name" << SEPARATOR;
        std::wcout.width(SECOND_ROW); std::wcout << L"PID" << SEPARATOR;
        std::wcout.width(THIRD_ROW);  std::wcout << L"Parent PID" << std::endl;

        do {
            std::wcout.width(FIRST_ROW);
            std::wcout << peProcessEntry.szExeFile << SEPARATOR;
            std::wcout.width(SECOND_ROW);
            std::wcout << peProcessEntry.th32ProcessID << SEPARATOR;
            std::wcout.width(THIRD_ROW);
            std::wcout << peProcessEntry.th32ParentProcessID << std::endl;

        } while (Process32Next(snap, &peProcessEntry));
    }catch (char* msg){std::wcout << L"ERROR : " << msg << std::endl;}

    system("pause");
}
