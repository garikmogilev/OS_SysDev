#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>
#include <sys/wait.h>

void useless_load(int count, char const* name, pid_t pid, int val_nice){
    int new_nice = nice(val_nice);
    for(int i = 0; i < count; i++){
        printf("i: %d name: %s  pid: %d priority: %d\n", i, name, pid, getpriority(PRIO_PROCESS, 0));
        sleep(1);
    }
}

int main() {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("error create child process"); exit(-1);
        case 0:
            printf( "success create process child\n");
            printf( "identifier of child process: %d ", pid);
            printf( "run cycle child\n");
            useless_load(10000, "child", pid, -10);
            printf( "child exit\n");
            exit(0);
        default:
            printf("main process\n");
            printf("identifier of main process: %d \n", getpid());
            printf("run cycle main\n");
            useless_load(10000, "main",getpid(),0);
            wait(NULL);
    }
    return 0;
}