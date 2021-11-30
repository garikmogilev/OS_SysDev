// OS08_02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	clock_t t1;
	clock_t t2;

	t1 = clock();

	for (long long i = 0;; i++) {
		t2 = clock();
		if ((t2 - t1) == 5000)
			std::cout << "i: " << i << std::endl;
		else if ((t2 - t1) == 10000)
			std::cout<< "i: " << i << std::endl;
		else if ((t2 - t1) == 15000)
		{
			std::cout << "i: " << i << std::endl;
			break;
		}
	}
	std::cout << "end" << std::endl;
}