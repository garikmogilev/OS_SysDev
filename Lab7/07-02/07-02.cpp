#include <Windows.h>
#include <iostream>

using namespace std;

DWORD pid = NULL;

CRITICAL_SECTION critical_section;

void CriticalLoop(const char* threadName)
{
	for (int i = 0; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&critical_section);
		}

		if (i == 61)
		{
			LeaveCriticalSection(&critical_section);
			Sleep(100);
			EnterCriticalSection(&critical_section);
		}

		if (i == 62)
		{
			LeaveCriticalSection(&critical_section);
		}

		cout << "\n" << threadName << ": " << i << "\n";
		Sleep(100);
	}
}

DWORD WINAPI ChildThread_A()
{
	CriticalLoop("Thread A");
	return 0;
}

DWORD WINAPI ChildThread_B()
{
	CriticalLoop("Thread B");
	return 0;
}

void main()
{
	pid = GetCurrentProcessId();

	DWORD tid = GetCurrentThreadId();

	DWORD ChildA_Id = NULL;
	DWORD ChildB_Id = NULL;

	InitializeCriticalSection(&critical_section);

	HANDLE hChildA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_A, NULL, 0, &ChildA_Id);
	HANDLE hChildB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_B, NULL, 0, &ChildB_Id);

	CriticalLoop("Main");

	WaitForSingleObject(hChildA, INFINITE);
	CloseHandle(hChildA);
	WaitForSingleObject(hChildB, INFINITE);
	CloseHandle(hChildB);

	DeleteCriticalSection(&critical_section);
}