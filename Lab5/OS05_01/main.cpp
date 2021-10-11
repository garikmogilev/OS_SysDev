#include <iostream>
#include <windows.h>

int main() {
    HANDLE handler = GetCurrentProcess();
    std::cout << "current PID:      " << GetCurrentProcessId()        << std::endl;
    std::cout << "thread ID         " << GetCurrentThreadId()         << std::endl;
    std::cout << "priority process  " << GetPriorityClass(handler)    << std::endl;
    return 0;
}
