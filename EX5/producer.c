#include "header.h"

int main() {
    key_t key = ftok("header.h", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int capacity;
    printf("Enter the Circular Queue capacity size: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0) {
        printf("Invalid capacity input.\n");
        return 1;
    }
    int s = shmget(key, sizeof(int) * (capacity + 2), IPC_CREAT | 0666);
    if (s == -1) {
        perror("Shmget failed");
        exit(1);
    }

    int *buf = (int *)shmat(s, NULL, 0);
    if (buf == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }
    int *in = &buf[capacity];
    int *out = &buf[capacity + 1];
    *in = 0;
    *out = 0;

    int sid = semget(key, 3, IPC_CREAT | 0666);
    if (sid == -1) {
        perror("semget failed");
        exit(1);
    }

    unsigned short values[3];
    values[MUTEX] = 1;
    values[FULL] = 0;
    values[EMPTY] = capacity;

    union semun snum;
    snum.array = values;
    semctl(sid, 0, SETALL, snum);

    int num;
    printf("[PRODUCER] Circular queue configuration ready. Enter numbers indefinitely (Ctrl+C to quit):\n");

    while (1) {
        printf("\nEnter number to enqueue: ");
        if (scanf("%d", &num) != 1) {
            break;
        }

        sem_wait(sid, EMPTY);
        sem_wait(sid, MUTEX);

        buf[*in] = num;
        printf(" -> [Enqueued] Value %d placed at Slot [%d]\n", num, *in);

        *in = (*in + 1) % capacity;

        sem_signal(sid, MUTEX);
        sem_signal(sid, FULL);
    }

    shmdt(buf);
    return 0;
}
