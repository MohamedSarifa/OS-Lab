#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid2, pid3;

    pid2 = fork();

    if (pid2 == 0)
    {
        // Inside P4
        printf("P2: PID=%d, Parent(P1) PID=%d\n", getpid(), getppid());
    }
    else
    {
        pid3 = fork();

        if (pid3 == 0)
        {
            // Inside P2
            printf("P3: PID=%d, Parent(P1) PID=%d\n", getpid(), getppid());
        }
        else
        {
            wait(NULL);
            wait(NULL);
            printf("P1: PID=%d, Parent PID=%d (All children finished)\n", getpid(), getppid());
        }
    }

    return 0;
}
