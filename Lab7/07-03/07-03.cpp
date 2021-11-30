#include <Windows.h>
#include <iostream>

using namespace std;

void CreateChildProcess(const char* procName, LPCWSTR& exePath, STARTUPINFO& startupAInfo, PROCESS_INFORMATION& procAInfo)
{
	ZeroMemory(&startupAInfo, sizeof(STARTUPINFO));
	startupAInfo.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(exePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupAInfo, &procAInfo))
	{
		cout << "CreateProcess:  " << procName << " is failed\n";
	}
}

void main()
{
	LPCWSTR exePath = L"D:\\GitHub\\OS_SysDev\\Lab7\\x64\\Debug\\07-03x.exe";
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procAInfo, procBInfo;

	HANDLE hm = CreateMutex(NULL, FALSE, L"OS07");

	CreateChildProcess("A", exePath, startupInfo, procAInfo);
	CreateChildProcess("B", exePath, startupInfo, procBInfo);


	for (int i = 0; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hm, INFINITE);
		}

		cout << "pid: " << GetCurrentProcessId() << ": " << i << "\n";
		Sleep(100);

		if (i == 61)
		{
			ReleaseMutex(hm);
			Sleep(100);
			WaitForSingleObject(hm, INFINITE);
		}

		if (i == 62)
		{
			ReleaseMutex(hm);
		}
	}

	WaitForSingleObject(&procAInfo, INFINITE);
	CloseHandle(procAInfo.hProcess);

	WaitForSingleObject(&procBInfo, INFINITE);
	CloseHandle(procBInfo.hProcess);

	CloseHandle(hm);
}