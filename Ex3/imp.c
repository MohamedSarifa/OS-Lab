#include "header.h"
void fcfs(int process[], int bursttime[], int arrivaltime[], int n)
{
    int current_time = 0;
    int total_wt = 0, total_tat = 0;

    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        if (current_time < arrivaltime[i])
            current_time = arrivaltime[i];

        wt[i] = current_time - arrivaltime[i];
        tat[i] = wt[i] + bursttime[i];

        current_time += bursttime[i];

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nFCFS Scheduling\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               process[i], arrivaltime[i], bursttime[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n",
           (float)total_tat / n);

    free(wt);
    free(tat);
}

/* ================= SJF (Non-Preemptive) ================= */

void sjf(int process[], int bursttime[], int arrivaltime[], int n)
{
    int completed = 0;
    int current_time = 0;
    int total_wt = 0, total_tat = 0;

    int *is_completed = (int *)calloc(n, sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));

    while (completed < n)
    {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (arrivaltime[i] <= current_time &&
                !is_completed[i] &&
                bursttime[i] < min_bt)
            {
                min_bt = bursttime[i];
                idx = i;
            }
        }

        if (idx == -1)
        {
            current_time++;
        }
        else
        {
            wt[idx] = current_time - arrivaltime[idx];
            tat[idx] = wt[idx] + bursttime[idx];

            current_time += bursttime[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];

            is_completed[idx] = 1;
            completed++;
        }
    }

    printf("\nSJF Scheduling\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               process[i], arrivaltime[i], bursttime[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n",
           (float)total_tat / n);

    free(is_completed);
    free(wt);
    free(tat);
}
void srtf(int process[], int bursttime[], int arrivaltime[], int n)
{
    int completed = 0;
    int current_time = 0;
    int total_wt = 0, total_tat = 0;

    int *rt = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        rt[i] = bursttime[i];

    while (completed < n)
    {
        int idx = -1;
        int min_rt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (arrivaltime[i] <= current_time && rt[i] > 0 && rt[i] < min_rt)
            {
                min_rt = rt[i];
                idx = i;
            }
        }

        if (idx == -1)
        {
            current_time++;
        }
        else
        {
            rt[idx]--;
            current_time++;

            if (rt[idx] == 0)
            {
                completed++;
                tat[idx] = current_time - arrivaltime[idx];
                wt[idx] = tat[idx] - bursttime[idx];

                total_wt += wt[idx];
                total_tat += tat[idx];
            }
        }
    }

    printf("\nSRTF Scheduling\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               process[i], arrivaltime[i], bursttime[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);

    free(rt); free(wt); free(tat);
}

void priority_np(int process[], int bursttime[], int arrivaltime[], int priority[], int n, int order)
{
    int completed = 0, current_time = 0, total_wt = 0, total_tat = 0;
    int *is_completed = (int *)calloc(n, sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));

    while (completed < n)
    {
        int idx = -1;
        // If order == 1, look for minimum number. If order == 2, look for maximum number.
        int target_priority = (order == 1) ? INT_MAX : INT_MIN;

        for (int i = 0; i < n; i++)
        {
            if (arrivaltime[i] <= current_time && !is_completed[i])
            {
                // Condition for lower number = higher priority
                if (order == 1 && priority[i] < target_priority) {
                    target_priority = priority[i];
                    idx = i;
                }
                // Condition for higher number = higher priority
                else if (order == 2 && priority[i] > target_priority) {
                    target_priority = priority[i];
                    idx = i;
                }
                // Tie-breaker: earlier arrival time
                else if (priority[i] == target_priority && idx != -1) {
                    if (arrivaltime[i] < arrivaltime[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            wt[idx] = current_time - arrivaltime[idx];
            tat[idx] = wt[idx] + bursttime[idx];
            current_time += bursttime[idx];
            total_wt += wt[idx];
            total_tat += tat[idx];
            is_completed[idx] = 1;
            completed++;
        }
    }

    printf("\nPriority Scheduling (Non-Preemptive)\nPID\tPri\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) printf("%d\t%d\t%d\t%d\t%d\t%d\n", process[i], priority[i], arrivaltime[i], bursttime[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time = %.2f\nAverage Turnaround Time = %.2f\n", (float)total_wt / n, (float)total_tat / n);
    free(is_completed); free(wt); free(tat);
}
void priority_p(int process[], int bursttime[], int arrivaltime[], int priority[], int n, int order)
{
    int completed = 0, current_time = 0, total_wt = 0, total_tat = 0;
    int *is_completed = (int *)calloc(n, sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));
    int *remaining_bt = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) remaining_bt[i] = bursttime[i];

    while (completed < n)
    {
        int idx = -1;
        int target_priority = (order == 1) ? INT_MAX : INT_MIN;

        for (int i = 0; i < n; i++)
        {
            if (arrivaltime[i] <= current_time && !is_completed[i])
            {
                if (order == 1 && priority[i] < target_priority) {
                    target_priority = priority[i];
                    idx = i;
                }
                else if (order == 2 && priority[i] > target_priority) {
                    target_priority = priority[i];
                    idx = i;
                }
                else if (priority[i] == target_priority && idx != -1) {
                    if (arrivaltime[i] < arrivaltime[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            remaining_bt[idx]--;
            current_time++;

            if (remaining_bt[idx] == 0) {
                tat[idx] = current_time - arrivaltime[idx];
                wt[idx] = tat[idx] - bursttime[idx];
                total_wt += wt[idx];
                total_tat += tat[idx];
                is_completed[idx] = 1;
                completed++;
            }
        }
    }

    printf("\nPriority Scheduling (Preemptive)\nPID\tPri\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) printf("%d\t%d\t%d\t%d\t%d\t%d\n", process[i], priority[i], arrivaltime[i], bursttime[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time = %.2f\nAverage Turnaround Time = %.2f\n", (float)total_wt / n, (float)total_tat / n);
    free(is_completed); free(wt); free(tat); free(remaining_bt);
}

/* ================= Round Robin (RR) ================= */

void round_robin(int process[], int bursttime[], int arrivaltime[], int n, int quantum)
{
    int completed = 0;
    int current_time = 0;
    int total_wt = 0, total_tat = 0;

    int *rt = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));
    int *in_queue = (int *)calloc(n, sizeof(int));

    // Ready Queue implementation elements
    int *queue = (int *)malloc(1000 * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bursttime[i];

    // Find the first process that arrives
    int min_at = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (arrivaltime[i] < min_at)
            min_at = arrivaltime[i];
    }

    current_time = min_at;

    // Push all processes arriving at the start time into the queue
    for (int i = 0; i < n; i++)
    {
        if (arrivaltime[i] == current_time)
        {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (completed < n)
    {
        if (front == rear) // Queue is empty
        {
            current_time++;
            for (int i = 0; i < n; i++)
            {
                if (arrivaltime[i] == current_time && !in_queue[i])
                {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++]; // Dequeue

        if (rt[idx] > quantum)
        {
            current_time += quantum;
            rt[idx] -= quantum;
        }
        else
        {
            current_time += rt[idx];
            rt[idx] = 0;
            completed++;

            tat[idx] = current_time - arrivaltime[idx];
            wt[idx] = tat[idx] - bursttime[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];
        }

        // Check for new arrivals while the process was running
        for (int i = 0; i < n; i++)
        {
            if (arrivaltime[i] <= current_time && !in_queue[i])
            {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        // Re-queue current process if it is not finished
        if (rt[idx] > 0)
        {
            queue[rear++] = idx;
        }
    }

    printf("\nRound Robin Scheduling (Quantum = %d)\n", quantum);
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               process[i], arrivaltime[i], bursttime[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);

    free(rt);
    free(wt);
    free(tat);
    free(in_queue);
    free(queue);
}
