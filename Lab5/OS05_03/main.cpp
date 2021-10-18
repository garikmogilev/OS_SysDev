#include <iostream>
#include <synchapi.h>
#include "windows.h"
#include <dirent.h>
#include <bitset>
#define PAUSE 1000
#define COUNT 1000000

DWORD pid = GetCurrentProcessId();
char const* getPriorityThreadToString(int);

DWORD WINAPI TA(){
    HANDLE thread = GetCurrentThread();
    DWORD  tid = GetCurrentThreadId();

    for (int i = 0; i < COUNT; ++i) {

        if((i % 1000) == 0) {
            Sleep(200);
            std::cout << "i:" << i << "\ttid: " << tid << "\t" << getPriorityThreadToString(GetThreadPriority(thread)) << std::endl;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    DWORD mask;
    DWORD priority_process;
    int priority_thread_1;
    int priority_thread_2;
    char *end;

    try {
        if (argc > 4) {
            mask                = strtol(argv[1], &end, 10);
            priority_process    = strtol(argv[2], &end, 10);
            priority_thread_1   = strtol(argv[3], &end, 10);
            priority_thread_2   = strtol(argv[4], &end, 10);
        } else {
            throw "not exist parameters (mask, priority_process , priority_thread_1, priority_thread_2)";
        }
    }catch (const char* exception){
        std::cerr << "Error: " << exception << '\n';
        system("pause");
        exit(-1);

    }

    HANDLE handler = GetCurrentProcess();
    SetPriorityClass(handler, priority_process);

    bool success = SetProcessAffinityMask(handler,mask);

    if(success) {
        ULONG_PTR processAffinityMask;
        ULONG_PTR systemAffinityMask;
        success = GetProcessAffinityMask(handler, &processAffinityMask, &systemAffinityMask);
        if(success){
            std::cout << "process mask           " << std::showbase << std::bitset<8>(processAffinityMask) << std::endl;
        }
    }

    HANDLE hChild_1 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&TA) , nullptr, 0, nullptr);

    HANDLE hChild_2 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&TA), nullptr, 0, nullptr);

    SetThreadPriority(hChild_1, priority_thread_1);
    SetThreadPriority(hChild_2, priority_thread_2);

    ResumeThread(hChild_1);
    ResumeThread(hChild_2);

    WaitForSingleObject(hChild_1, INFINITE);
    WaitForSingleObject(hChild_2, INFINITE);
    CloseHandle(hChild_1);
    CloseHandle(hChild_2);
    system("pause");
    return 0;
}

char const* getPriorityThreadToString(int priority)
{
    switch (priority) {
        case THREAD_PRIORITY_IDLE:          return "THREAD_PRIORITY_IDLE";
        case THREAD_PRIORITY_LOWEST:        return "THREAD_PRIORITY_LOWEST";
        case THREAD_PRIORITY_BELOW_NORMAL:  return "THREAD_PRIORITY_BELOW_NORMAL";
        case THREAD_PRIORITY_NORMAL:        return "THREAD_PRIORITY_NORMAL";
        case THREAD_PRIORITY_ABOVE_NORMAL:  return "THREAD_PRIORITY_ABOVE_NORMAL";
        case THREAD_PRIORITY_HIGHEST:       return "THREAD_PRIORITY_HIGHEST";
        case THREAD_PRIORITY_TIME_CRITICAL: return "THREAD_PRIORITY_TIME_CRITICAL";
        default:                            return "I'm crashed...";
    }

}