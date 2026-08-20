#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    key_t key;
    int shmid;
    char *str;
    int i, len;

    key = ftok("shmfile", 65);

    shmid = shmget(key, 1024, 0666);

    str = (char *)shmat(shmid, NULL, 0);

    printf("String received: %s", str);

    len = strlen(str);

    printf("Reverse of the string: ");

    for(i = len - 1; i >= 0; i--)
    {
        if(str[i] != '\n')
            printf("%c", str[i]);
    }

    printf("\n");

    shmdt(str);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
