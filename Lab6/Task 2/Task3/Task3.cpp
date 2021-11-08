#include <iostream>
#include <windows.h>
#define KB (1024)
#define MB (KB * KB)
#define SIZE_PAGE (4 * KB)
#define QUANTITY_PAGES 256

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int* arrayint;

    LPVOID xmemaddr = VirtualAlloc(NULL, QUANTITY_PAGES * SIZE_PAGE, MEM_COMMIT, PAGE_READWRITE);
    std::cout << "size: " << QUANTITY_PAGES * SIZE_PAGE / KB << " KB" << std::endl;
    std::cout << std::hex << xmemaddr << std::endl;

    arrayint = (int*)xmemaddr;

    int const count = QUANTITY_PAGES * SIZE_PAGE / sizeof(int);

    if (arrayint == nullptr) {
        std::cout << "ERROR: VirtualAlloc(...)";
        exit(-1);
    }

    for (int i = 0; i < count; i++)
    {
        *arrayint = i;
        arrayint++;
    }

    // С И А      С = D1; И = C8; A = C0;

    int page = 0xD1;
    int offset = 0xC8C;

    std::cout << "" << * (int*)(((int*)xmemaddr + (SIZE_PAGE)*page / sizeof(int) + offset / sizeof(int)));
    system("pause");
}

