#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    key_t key;
    int shmid;
    char *str;

    key = ftok("shmfile", 65);

    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    str = (char *)shmat(shmid, NULL, 0);

    printf("Enter a string: ");
    fgets(str, 1024, stdin);

    printf("String written to shared memory.\n");

    shmdt(str);

    return 0;
}
