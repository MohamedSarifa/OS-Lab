#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key;
    int msgid;
    struct message msg;
    int i, count = 0;

    key = ftok("msgfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);

    printf("Message received: %s", msg.msg_text);

    for(i = 0; msg.msg_text[i] != '\0'; i++)
    {
        if(msg.msg_text[i] != ' ' &&
           (msg.msg_text[i + 1] == ' ' ||
            msg.msg_text[i + 1] == '\n' ||
            msg.msg_text[i + 1] == '\0'))
        {
            count++;
        }
    }

    printf("Number of words = %d\n", count);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
