#include <iostream>
#include <unistd.h>

int main() {
    std::cout << "OS03_04" << std::endl;\
    pid_t pid = getpid();
    for (int i = 0; i < 1000; ++i) {
        std::cout << "i: " << i << ", pid: " << pid << std::endl;
        sleep(1);
    }
    return 0;
}
