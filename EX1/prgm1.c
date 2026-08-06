#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("P2: PID = %d, Parent PID = %d\n",
               getpid(), getppid());
    }
    else
    {
       wait(NULL);
        printf("P1: PID = %d (PARENT)\n",
               getpid());
    }

    return 0;
}
