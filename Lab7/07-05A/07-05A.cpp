#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    DWORD pid = GetCurrentProcessId();
    HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"event");

    if (he == NULL) 
        cout << "Failed open event" << endl;

    if (he != 0)
        WaitForSingleObject(he, INFINITE);

    for (int i = 0; i < 90; i++)
    {
        cout << pid << " OS07_05A " << i << endl;
        Sleep(100);
    }

    if(he != 0)
        CloseHandle(he);
}