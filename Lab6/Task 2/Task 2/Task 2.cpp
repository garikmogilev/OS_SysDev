#include <iostream>
#include "windows.h"
#define COUNT 10000000

int main()
{
	for (int i = 0; i < COUNT; i++)
	{
		std::cout << i << std::endl;
		Sleep(200);
	}
}

