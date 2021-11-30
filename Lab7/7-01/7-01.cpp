#include <iostream>
#include <Windows.h>

using namespace std;

extern "C" HANDLE CreateThreadInAsm(int*);

int main() {

	int i = 0;

	HANDLE thread1;
	HANDLE thread2;

	thread1 = CreateThreadInAsm(&i);
	thread2 = CreateThreadInAsm(&i);

	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);

	cout << "result: " << i;

	return 0;


}