#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    int n;
    pid_t pid;

    pipe(fd);

    pid = fork();

    if(pid > 0)
    {
        close(fd[1]);

        read(fd[0], &n, sizeof(n));

        int temp = n;

        while(temp > 1 && temp % 3 == 0)
        {
            temp = temp / 3;
        }

        printf("Parent Id=%d\n",getpid());
        if(temp == 1)
            printf("%d is Power of 3\n", n);
        else
            printf("%d is NOT Power of 3\n", n);

        close(fd[0]);
    }
    else
    {
        close(fd[0]);

        printf("Child Id=%d,Parent Id=%d\n",getpid(),getppid());
        printf("Enter a number: ");
        scanf("%d",&n);

        write(fd[1], &n, sizeof(n));

        close(fd[1]);
    }

    return 0;
}
