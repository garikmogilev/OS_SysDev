#include <iostream>

int main()
{
    time_t t1;
    tm ttm;
    t1 = time(&t1);

    localtime_s(&ttm, &t1);

    std::cout << ttm.tm_mday << "." << ttm.tm_mon << "." << (1900 + ttm.tm_year) << " " <<
        ttm.tm_hour << "." << ttm.tm_min << "." << ttm.tm_sec << std::endl;

}