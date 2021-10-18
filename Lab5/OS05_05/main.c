#include <stdio.h>
#include <unistd.h>
#define COUNT 10000000

int main(int argc, char **argv)
{
    for(int i = 0; i < COUNT; i++)
    {
        printf("pid: %d priority: %d\n", getpid(), nice(0));
        sleep(1);
    }
}