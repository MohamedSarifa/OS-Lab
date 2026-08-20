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

    key = ftok("msgfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    msg.msg_type = 1;

    printf("Enter a message: ");
    fgets(msg.msg_text, 100, stdin);

    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);

    printf("Message sent successfully.\n");

    return 0;
}
