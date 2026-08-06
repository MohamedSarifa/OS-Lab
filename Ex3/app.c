#include "header.h"
#include <limits.h> // Necessary for INT_MAX/INT_MIN

int main()
{
    int n, i, choice;
    int priority_order = 1; // Default: 1: Low number = High Priority

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0)
        return 0;

    int *process = (int *)malloc(n * sizeof(int));
    int *burst = (int *)malloc(n * sizeof(int));
    int *arrival = (int *)malloc(n * sizeof(int));
    int *priority = (int *)malloc(n * sizeof(int));
    int *temp_burst = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        process[i] = i + 1;
        printf("\nFor Process %d\n", process[i]);
        printf("Arrival Time : ");
        scanf("%d", &arrival[i]);
        printf("Burst Time   : ");
        scanf("%d", &burst[i]);
        printf("Priority     : ");
        scanf("%d", &priority[i]);
    }

    do {
        printf("\n========== CPU Scheduling ==========\n");
        printf("1. FCFS\n");
        printf("2. SJF (Non-Preemptive)\n");
        printf("3. SRTF (Preemptive)\n");
        printf("4. Priority (Non-Preemptive)\n");
        printf("5. Priority (Preemptive)\n");
        printf("6. Round Robin\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        for (i = 0; i < n; i++) {
            temp_burst[i] = burst[i];
        }

        switch (choice)
        {
            case 1: fcfs(process, temp_burst, arrival, n); break;
            case 2: sjf(process, temp_burst, arrival, n); break;
            case 3: srtf(process, temp_burst, arrival, n); break;

            case 4:
                printf("\nPriority Mode:\n1. Lower number = Higher Priority\n2. Higher number = Higher Priority\nEnter mode: ");
                scanf("%d", &priority_order);
                priority_np(process, temp_burst, arrival, priority, n, priority_order);
                break;

            case 5:
                printf("\nPriority Mode:\n1. Lower number = Higher Priority\n2. Higher number = Higher Priority\nEnter mode: ");
                scanf("%d", &priority_order);
                priority_p(process, temp_burst, arrival, priority, n, priority_order);
                break;

            case 6:
                {
                    int quantum;
                    printf("Enter Time Quantum: ");
                    scanf("%d", &quantum);
                    round_robin(process, temp_burst, arrival, n, quantum);
                }
                break;

            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid Choice!\n"); break;
        }
    } while (choice < 7);

    free(process); free(burst); free(arrival); free(priority); free(temp_burst);
    return 0;
}
