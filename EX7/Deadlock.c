#include <stdio.h>

int isSafeSystem(int n, int m, int allocation[10][10], int need[10][10], int available[10], int safe[10]);

int main()
{
    int n, m;
    int allocation[10][10];
    int max[10][10];
    int need[10][10];
    int available[10];
    int safe[10];
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    if (n > 10 || m > 10 || n <= 0 || m <= 0)
    {
        printf("Error: Number of processes/resources must be between 1 and 10.\n");
        return 1;
    }

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\n--- Checking Initial System Safety ---\n");
    int initiallySafe = isSafeSystem(n, m, allocation, need, available, safe);

    if (initiallySafe)
    {
        printf("Initial System is in a SAFE state.\n");
        printf("Initial Safe Sequence: ");
        for(i = 0; i < n; i++)
        {
            printf("P%d", safe[i]);
            if(i != n - 1) printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        printf("Initial System is in an UNSAFE state! Deadlock may occur even without new requests.\n");
        printf("Resource requests are disabled until the baseline system is resolved.\n");
        return 1;
    }

    int req_process;
    int request[10];
    char choice;

    printf("\nDo you want to make a resource request? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        printf("Enter the process number making the request (0 to %d): ", n - 1);
        scanf("%d", &req_process);

        if (req_process >= n || req_process < 0)
        {
            printf("Error: Invalid process number.\n");
            return 1;
        }

        printf("Enter the request vector for P%d:\n", req_process);
        for (j = 0; j < m; j++)
        {
            scanf("%d", &request[j]);
        }

        for (j = 0; j < m; j++)
        {
            if (request[j] > need[req_process][j])
            {
                printf("\nError: Process P%d has exceeded its maximum claim (Request > Need).\n", req_process);
                return 1;
            }
        }

        for (j = 0; j < m; j++)
        {
            if (request[j] > available[j])
            {
                printf("\nProcess P%d must wait. Resources are not available (Request > Available).\n", req_process);
                return 1;
            }
        }

        for (j = 0; j < m; j++)
        {
            available[j] -= request[j];
            allocation[req_process][j] += request[j];
            need[req_process][j] -= request[j];
        }

        printf("\n--- Checking System Safety After Request ---\n");
        int postRequestSafe = isSafeSystem(n, m, allocation, need, available, safe);

        if(postRequestSafe)
        {
            printf("\nSystem remains in a SAFE state.\n");
            printf("The request by P%d can be safely granted immediately.\n", req_process);
            printf("New Safe Sequence: ");
            for(i = 0; i < n; i++)
            {
                printf("P%d", safe[i]);
                if(i != n - 1) printf(" -> ");
            }
            printf("\n");
        }
        else
        {
            printf("\nSystem would transition into an UNSAFE state.\n");
            printf("The request by P%d CANNOT be granted immediately as it leaves the system unsafe (Potential Deadlock).\n", req_process);

            for (j = 0; j < m; j++)
            {
                available[j] += request[j];
                allocation[req_process][j] -= request[j];
                need[req_process][j] += request[j];
            }
            printf("System resources have been rolled back to their original state.\n");
        }
    }

    return 0;
}

int isSafeSystem(int n, int m, int allocation[10][10], int need[10][10], int available[10], int safe[10])
{
    int work[10];
    int finish[10] = {0};
    int count = 0;
    int i, j, k;

    for (j = 0; j < m; j++)
    {
        work[j] = available[j];
    }

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int canExecute = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        canExecute = 0;
                        break;
                    }
                }

                if(canExecute)
                {
                    for(k = 0; k < m; k++)
                    {
                        work[k] = work[k] + allocation[i][k];
                    }

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            break;
        }
    }

    return (count == n);
}
