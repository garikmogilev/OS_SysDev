#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000

using namespace std;
HANDLE timer;
int i = 1;

DWORD WINAPI ChildThread()
{
    clock_t t1 = clock();
    int counter = 1;

    while (true)
    {
        clock_t t2 = clock();

        if (((t2 - t1) * counter) >= 15000)
        {
            counter++;

            cout << " time: " << (t2 - t1) / CLOCKS_PER_SEC * counter << "s i: " << i << endl;
            ExitProcess(0);
        }

        else if ((t2 - t1) >= 3000 && (t2 - t1) != 0)
        {
            cout << " time: " << (t2 - t1)/CLOCKS_PER_SEC * counter <<  "s i: " << i << endl;
            counter++;
            t1 = clock();
        }


        WaitForSingleObject(timer, INFINITE);
        i++;
    }
    return 0;
}

int main()
{
    long long it = - 0 * SECOND;
    DWORD ChildId = 0;
    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, NULL, &ChildId);
    timer = CreateWaitableTimer(NULL, FALSE, NULL);

    if (!SetWaitableTimer(timer, (LARGE_INTEGER*)&it, 1000, NULL, NULL, FALSE)) 
        throw "Error SetWaitableTimer";

    WaitForSingleObject(hChild, INFINITE);
    return 0;
}