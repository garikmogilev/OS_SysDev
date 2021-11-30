#include <Windows.h>
#include <iostream>

using namespace std;

void CreateChildProcess(const char* procName, LPCWSTR& exePath, STARTUPINFO& startupAInfo, PROCESS_INFORMATION& procAInfo)
{
	ZeroMemory(&startupAInfo, sizeof(STARTUPINFO));
	startupAInfo.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(exePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupAInfo, &procAInfo))
	{
		cout << "proc " << procName << " not created\n";
	}
}

int main()
{
	LPCWSTR exePath = L"D:\\GitHub\\OS_SysDev\\Lab7\\x64\\Debug\\07-04x.exe";
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procAInfo, procBInfo;
	CreateChildProcess("A", exePath, startupInfo, procAInfo);
	CreateChildProcess("B", exePath, startupInfo, procBInfo);

	HANDLE hs = CreateSemaphore(NULL, 2, 2, L"semaphore");

	for (int i = 0; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hs, INFINITE);
		}

		cout << "pid: " << GetCurrentProcessId() << " " << i << "\n";
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

	WaitForSingleObject(&procAInfo, INFINITE);
	CloseHandle(procAInfo.hProcess);

	WaitForSingleObject(&procBInfo, INFINITE);
	CloseHandle(procBInfo.hProcess);

	CloseHandle(hs);
	return 0;
}