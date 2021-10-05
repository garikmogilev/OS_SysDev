#include <iostream>
#include "windows.h"
#define PAUSE 1000

DWORD pid = GetCurrentProcessId();

DWORD WINAPI ThreadProc_1(){
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; ++i) {
        std::cout << "child 1 " << ", PID: " << pid << ", TID: " << tid << std::endl;
        Sleep(PAUSE);
    }
    return 0;
}

DWORD WINAPI ThreadProc_2(){
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 125; ++i) {
        std::cout << "child 2 " << ", PID: " << pid << ", TID: " << tid << std::endl;
        Sleep(PAUSE);
    }
    return 0;
}

int main() {
    DWORD tid = GetCurrentThreadId();

    HANDLE hChild_1 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&ThreadProc_1), nullptr, 0, nullptr);
    Sleep(PAUSE/3);
    HANDLE hChild_2 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&ThreadProc_2), nullptr, 0, nullptr);
    Sleep(PAUSE/3);

    for (int i = 0; i < 100; ++i) {

        if(i == 20)
            SuspendThread(hChild_1);
        if(i == 40)
            SuspendThread(hChild_2);
        if(i == 60)
            ResumeThread(hChild_1);

        std::cout << "main i: " << i << ", PID: " << pid << ", TID: " << tid << std::endl;
        Sleep(PAUSE);
    }
    ResumeThread(hChild_2);

    WaitForSingleObject(hChild_1, INFINITE);
    WaitForSingleObject(hChild_2, INFINITE);
    CloseHandle(hChild_1);
    CloseHandle(hChild_2);

    return 0;
}
