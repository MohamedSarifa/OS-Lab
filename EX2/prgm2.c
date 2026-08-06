#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int p1[2], p2[2];
    char str[100];
    char status[20];

    pipe(p1);
    pipe(p2);

    if(fork() > 0)
    {

        close(p1[0]);
        close(p2[1]);

        printf("Parent Id=%d\n",getpid());
        printf("Enter a string: ");
        scanf("%s", str);

        write(p1[1], str, sizeof(str));

        read(p2[0], status, sizeof(status));

        printf("Status: %s\n", status);

        close(p1[1]);
        close(p2[0]);
    }
    else
    {

        close(p1[1]);
        close(p2[0]);

        read(p1[0], str, sizeof(str));

        int len = strlen(str);
        int digit = 0;
        int special = 0;

        int i;
        for(i=0; str[i]!='\0'; i++)
        {
            if(isdigit(str[i]))
                digit = 1;

            else if(!isalnum(str[i]))
                special = 1;
        }
        printf("Child Process:%d,Parent Process:%d\n",getpid(),getppid());
        if(len > 7 && digit && special)
            strcpy(status,"VALID");
        else
            strcpy(status,"INVALID");

        write(p2[1], status, sizeof(status));

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
