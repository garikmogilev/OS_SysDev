#include <Windows.h>
#include <iostream>

using namespace std;

void main()
{
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"semaphore");
	if (hs == NULL)
	{
		cout << "Semaphore is failed on open\n";
	}
	else
	{
		cout << "Semaphore is open\n";
	}

	DWORD pid = GetCurrentProcessId();

	for (int i = 0; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hs, INFINITE);
		}

		cout << "pid: " << GetCurrentProcessId() << ": " << i << "\n";
		Sleep(100);

		if (i == 61)
		{
			ReleaseSemaphore(hs, 1, 0);
			Sleep(100);
			WaitForSingleObject(hs, INFINITE);
		}

		if (i == 62)
		{
			ReleaseSemaphore(hs, 1, 0);
		}
	}

	CloseHandle(hs);
}