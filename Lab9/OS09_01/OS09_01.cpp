#include <iostream>
#include <windows.h>
#include <string>
#include <wchar.h>

using namespace std;

bool printFileInfo(LPCWSTR fileName) {
    HANDLE fileIn;
    BY_HANDLE_FILE_INFORMATION bhfi;

    if ((fileIn = CreateFile(
        fileName, 
        GENERIC_READ,
        0, 
        0, 
        OPEN_EXISTING, 
        0, 
        0)
        ) ==
        INVALID_HANDLE_VALUE) {
        cerr << "Error opening source: " <<
            GetLastError() << endl;
        exit(1);
    }

    if (GetFileInformationByHandle(fileIn,
        &bhfi)) {
        cout << "Created: " <<
            bhfi.dwFileAttributes <<
            endl;
    }
	return true;
}
int main()
{
	const LPCWSTR file = (LPCWSTR)L"D:\\GitHub\\OS_SysDev\\Lab9\\OS09_01.txt";
	wcout << file;
	printFileInfo(file);
}