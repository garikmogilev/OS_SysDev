#include <iostream>
#include <unistd.h>
#include <wait.h>

void useless_load(int count, char const* name, pid_t pid){
    for(int i = 0; i < count; i++){
        std::cout << "i:" << i << " " << name << ", pid:" << pid <<  std::endl;
        sleep(1);
    }
}

int main() {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("error create child process"); exit(-1);
        case 0:
            std::cout << "success create process child " << std::endl;
            std::cout << "identifier of child process: " << pid<< std::endl << std::endl;
            std::cout << "run cycle child" << std::endl;
            useless_load(50, "child", pid);
            std::cout << "child exit" << std::endl;
            exit(0);
        default:
            std::cout << "main process" << std::endl;
            std::cout << "identifier of main process: " << getpid() << std::endl << std::endl;
            std::cout << "run cycle main" << std::endl;
            useless_load(100, "main",getpid());
            wait(nullptr);
    }
    return 0;
}
