#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000;

using namespace std;

LPCWSTR an = L"D:/GitHub/OS_SysDev/Lab8/x64/Debug/OS08_04x.exe";

DWORD WINAPI ChildThreadProcess1()
{
    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;
    ZeroMemory(&si1, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO);

    if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
        cout << endl << "Process first created" << endl;
    else cout << endl << "Process first not created" << endl;

    WaitForSingleObject(pi1.hProcess, 60000);
    TerminateProcess(pi1.hProcess, 0);
    cout << "Process 1 ended" << endl;
    return 0;
}

DWORD WINAPI ChildThreadProcess2()
{
    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;
    ZeroMemory(&si2, sizeof(STARTUPINFO));
    si2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
        cout << "Process second created" << endl;
    else cout << endl << "Process 2 not created" << endl;

    WaitForSingleObject(pi2.hProcess, 120000);
    TerminateProcess(pi2.hProcess, 0);
    cout << "Process second ended" << endl;

    return 0;
}

int main()
{
    DWORD ChildId1 = 0;
    DWORD ChildId2 = 0;
    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadProcess1, NULL, NULL, &ChildId1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadProcess2, NULL, NULL, &ChildId2);

    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);
}