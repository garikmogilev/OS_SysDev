#include <iostream>
#include "windows.h"
#define COUNT 1000000
using namespace std;

char const* getPriorityProcessToString(DWORD);
char const* getPriorityThreadToString(int);

int main() {

    HANDLE handler = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    for (int i = 0; i < COUNT; ++i) {
        if((i % 1000) == 0){
            cout << "i:                     " << i                                                          << endl;
            cout << "current PID:           " << GetCurrentProcessId()                                      << endl;
            cout << "thread ID              " << GetCurrentThreadId()                                       << endl;
            cout << "priority process       " << getPriorityProcessToString(GetPriorityClass(handler))      << endl;
            cout << "priority thread        " << getPriorityThreadToString(GetThreadPriority(thread))       << endl;
            Sleep(200);
        }
    }

    return 0;
}

char const* getPriorityProcessToString(DWORD priority)
{
    switch (priority)
    {
        case IDLE_PRIORITY_CLASS:           return "IDLE_PRIORITY_CLASS";
        case BELOW_NORMAL_PRIORITY_CLASS:   return "BELOW_NORMAL_PRIORITY_CLASS";
        case NORMAL_PRIORITY_CLASS:         return "NORMAL_PRIORITY_CLASS";
        case ABOVE_NORMAL_PRIORITY_CLASS:   return "ABOVE_NORMAL_PRIORITY_CLASS";
        case HIGH_PRIORITY_CLASS:           return "HIGH_PRIORITY_CLASS";
        case REALTIME_PRIORITY_CLASS:       return "REALTIME_PRIORITY_CLASS";
        default:                            return "I'm crashed...";
    }

}

char const* getPriorityThreadToString(int priority)
{
    switch (priority) {
        case THREAD_PRIORITY_IDLE:          return "THREAD_PRIORITY_IDLE\n";
        case THREAD_PRIORITY_LOWEST:        return "THREAD_PRIORITY_LOWEST\n";
        case THREAD_PRIORITY_BELOW_NORMAL:  return "THREAD_PRIORITY_BELOW_NORMAL\n";
        case THREAD_PRIORITY_NORMAL:        return "THREAD_PRIORITY_NORMAL\n";
        case THREAD_PRIORITY_ABOVE_NORMAL:  return "THREAD_PRIORITY_ABOVE_NORMAL\n";
        case THREAD_PRIORITY_HIGHEST:       return "THREAD_PRIORITY_HIGHEST\n";
        case THREAD_PRIORITY_TIME_CRITICAL: return "THREAD_PRIORITY_TIME_CRITICAL\n";
        default:                            return "I'm crashed...";
    }

}
