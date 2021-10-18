#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/resource.h>
#include <sched.h>
#include <stdio.h>
#include <linux/unistd.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdbool.h>

#define gettid() ((pid_t)syscall(SYS_gettid))

int main(int argc, char **argv)
{
    pid_t pid = getpid();
    pid_t tid = gettid();


    printf("pid: %d\n", pid);
    printf("tid: %d\n", tid);
    printf("current priority = %d\n", getpriority(PRIO_PROCESS,0));

    cpu_set_t set;
    CPU_ZERO(&set);
    if(sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0)
    {
        bool is_set = 0;
        for(int i = 0; i < CPU_SETSIZE; i++)
        {
            is_set = CPU_ISSET(i, &set);
            if(is_set)
            printf("using cpu = %d\n", i);
        }
    }
    else printf("sched_getaaffinity = ERROR");
}
