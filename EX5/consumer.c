#include "header.h"

int main() {
    key_t key = ftok("header.h", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int temp_s = shmget(key, 0, 0666);
    if (temp_s == -1) {
        perror("Shared memory block absent. Please launch producer window first.");
        exit(1);
    }

    struct shmid_ds shm_info;
    shmctl(temp_s, IPC_STAT, &shm_info);
    int capacity = (shm_info.shm_segsz / sizeof(int)) - 2;

    int s = shmget(key, sizeof(int) * (capacity + 2), 0666);
    int *buf = (int *)shmat(s, NULL, 0);

    int *out = &buf[capacity + 1];

    int sid = semget(key, 3, 0666);
    if (sid == -1) {
        perror("semget failed");
        exit(1);
    }

    printf("[CONSUMER] Connected to Circular Queue (Extracted Capacity: %d items).\n", capacity);
    printf("[CONSUMER] Actively listening for streaming memory blocks...\n");

    while (1) {
        sem_wait(sid, FULL);
        sem_wait(sid, MUTEX);

        int num = buf[*out];
        printf("\n <- [Dequeued] Removed from Slot [%d]: %d\n", *out, num);
        printf("    Square processing calculation: %d\n", num * num);

        *out = (*out + 1) % capacity;

        sem_signal(sid, MUTEX);
        sem_signal(sid, EMPTY);

        sleep(2);
    }

    shmdt(buf);
    return 0;
}
