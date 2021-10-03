#include <iostream>
#include <unistd.h>

int main() {
    std::cout << "OS03_06" << std::endl;
    system("./OS03_05_1");
    for (int i = 0; i < 100; ++i) {
        std::cout << "i:" << i << ", pid: " << getpid()  << std::endl;
        sleep(1);
    }

    return 0;
}

/*int main() {
    std::cout << "OS03_05_1" << std::endl;

    for (int i = 0; i < 50; ++i) {
        std::cout << "i:" << i << ", pid: " << getpid()  << std::endl;
        sleep(1);
    }
    return 0;
}*/
