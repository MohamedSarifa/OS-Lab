#include <stdio.h>

#define MAX 20


void firstFit(int block[], int process[], int nb, int np)
{
    int i, j;
    int allocation[MAX];
    int internal = 0;
    int external = 0;

    for(i = 0; i < np; i++)
        allocation[i] = -1;

    for(i = 0; i < np; i++)
    {
        for(j = 0; j < nb; j++)
        {
            if(block[j] >= process[i])
            {
                allocation[i] = j;

                internal = internal + (block[j] - process[i]);

                block[j] = block[j] - process[i];

                break;
            }
        }
    }

    for(i = 0; i < nb; i++)
        external = external + block[i];

    printf("\n========== FIRST FIT ==========\n");

    printf("Process\tSize\tBlock\n");

    for(i = 0; i < np; i++)
    {
        if(allocation[i] != -1)
        {
            printf("P%d\t%d\tB%d\n",
                   i + 1,
                   process[i],
                   allocation[i] + 1);
        }
        else
        {
            printf("P%d\t%d\tNot Allocated\n",
                   i + 1,
                   process[i]);
        }
    }

    printf("Internal Fragmentation = %d\n", internal);
    printf("External Fragmentation = %d\n", external);
}

void bestFit(int block[], int process[], int nb, int np)
{
    int i, j, best;
    int allocation[MAX];
    int internal = 0;
    int external = 0;

    for(i = 0; i < np; i++)
        allocation[i] = -1;

    for(i = 0; i < np; i++)
    {
        best = -1;

        for(j = 0; j < nb; j++)
        {
            if(block[j] >= process[i])
            {
                if(best == -1 || block[j] < block[best])
                {
                    best = j;
                }
            }
        }

        if(best != -1)
        {
            allocation[i] = best;

            internal = internal + (block[best] - process[i]);

            block[best] = block[best] - process[i];
        }
    }

    for(i = 0; i < nb; i++)
        external = external + block[i];

    printf("\n========== BEST FIT ==========\n");

    printf("Process\tSize\tBlock\n");

    for(i = 0; i < np; i++)
    {
        if(allocation[i] != -1)
        {
            printf("P%d\t%d\tB%d\n",
                   i + 1,
                   process[i],
                   allocation[i] + 1);
        }
        else
        {
            printf("P%d\t%d\tNot Allocated\n",
                   i + 1,
                   process[i]);
        }
    }

    printf("Internal Fragmentation = %d\n", internal);
    printf("External Fragmentation = %d\n", external);
}



void worstFit(int block[], int process[], int nb, int np)
{
    int i, j, worst;
    int allocation[MAX];
    int internal = 0;
    int external = 0;

    for(i = 0; i < np; i++)
        allocation[i] = -1;

    for(i = 0; i < np; i++)
    {
        worst = -1;

        for(j = 0; j < nb; j++)
        {
            if(block[j] >= process[i])
            {
                if(worst == -1 || block[j] > block[worst])
                {
                    worst = j;
                }
            }
        }

        if(worst != -1)
        {
            allocation[i] = worst;

            internal = internal + (block[worst] - process[i]);

            block[worst] = block[worst] - process[i];
        }
    }

    for(i = 0; i < nb; i++)
        external = external + block[i];

    printf("\n========== WORST FIT ==========\n");

    printf("Process\tSize\tBlock\n");

    for(i = 0; i < np; i++)
    {
        if(allocation[i] != -1)
        {
            printf("P%d\t%d\tB%d\n",
                   i + 1,
                   process[i],
                   allocation[i] + 1);
        }
        else
        {
            printf("P%d\t%d\tNot Allocated\n",
                   i + 1,
                   process[i]);
        }
    }

    printf("Internal Fragmentation = %d\n", internal);
    printf("External Fragmentation = %d\n", external);
}



int main()
{
    int block[MAX];
    int process[MAX];

    int b1[MAX];
    int b2[MAX];
    int b3[MAX];

    int nb, np;
    int i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    printf("\nEnter size of memory blocks:\n");

    for(i = 0; i < nb; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &block[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    printf("\nEnter size of processes:\n");

    for(i = 0; i < np; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &process[i]);
    }


    for(i = 0; i < nb; i++)
    {
        b1[i] = block[i];
        b2[i] = block[i];
        b3[i] = block[i];
    }

    firstFit(b1, process, nb, np);

    bestFit(b2, process, nb, np);

    worstFit(b3, process, nb, np);

    return 0;
}
