#include <iostream>
#include <windows.h>
#include <intrin.h>
#include <bitset>
using namespace std;

char const* getPriorityProcessToString(DWORD);
char const* getPriorityThreadToString(int);
int getQuantityProcessor(ULONG_PTR);
string getNumberProcess(ULONG_PTR);

int main()
{

    HANDLE handler = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    PDWORD_PTR processMask = nullptr, systemMask = nullptr;

    SetThreadPriority(thread, THREAD_PRIORITY_TIME_CRITICAL);
    SetPriorityClass(handler, REALTIME_PRIORITY_CLASS);
    ULONG_PTR processAffinityMask ;
    ULONG_PTR systemAffinityMask ;

    bool success = GetProcessAffinityMask(handler,&processAffinityMask,&systemAffinityMask);

    cout << "current PID:           " << GetCurrentProcessId()                                      << endl;
    cout << "thread ID              " << GetCurrentThreadId()                                       << endl;
    cout << "priority process       " << getPriorityProcessToString(GetPriorityClass(handler))      << endl;
    cout << "priority thread        " << getPriorityThreadToString(GetThreadPriority(thread))       << endl;

if(success) {
    cout << "process mask           " << showbase << bitset<8>(processAffinityMask)                 << endl;
    cout << "system mask            " << showbase << bitset<8>(systemAffinityMask)                  << endl;
    cout << "quantity processors    " << getQuantityProcessor(processAffinityMask)                  << endl;
    cout << "processors using       " << getNumberProcess(processAffinityMask)                      << endl;
}
    system("pause");
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

int getQuantityProcessor(ULONG_PTR affinityMask)
{
    int counter = 0;

    while (affinityMask != 0) {
        if(affinityMask & 0x1)
            counter += 1;
        affinityMask = affinityMask >> 1;
    }
    return counter;
}

string getNumberProcess(ULONG_PTR affinityMask)
{
    string processors = "using processors: ";

    for (int i = 0; affinityMask != 0; ++i)
    {
        if(affinityMask & 0x1)
            processors += to_string(i) + " ";
        affinityMask = affinityMask >> 1;
    }
    return processors;
}