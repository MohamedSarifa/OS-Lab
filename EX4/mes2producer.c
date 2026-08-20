#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
    long msg_type;
    int n;
    int marks[10];
};

int main()
{
    key_t key;
    int msgid, i;
    struct message msg;

    key = ftok("msgfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    msg.msg_type = 1;

    printf("Enter number of students: ");
    scanf("%d", &msg.n);

    for(i = 0; i < msg.n; i++)
    {
        printf("Enter mark of student %d: ", i + 1);
        scanf("%d", &msg.marks[i]);
    }

    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);

    printf("Marks sent successfully.\n");

    return 0;
}
