#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]){
    std::cout << "OS03_07" << std::endl;
    execv("./OS03_05_1", argv);
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
