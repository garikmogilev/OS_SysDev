#include <stdio.h>
#include <unistd.h>
#define COUNT 24700000

int main(int argc, char **argv)
{
    nice(-20);
    for(int i = 0; i < COUNT; i++)
    {
        printf("%d\n", getpid());
    }
}