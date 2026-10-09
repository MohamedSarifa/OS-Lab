#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void sort(int a[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void FCFS(int request[], int n, int head)
{
    int i, current = head, total = 0;

    printf("\nFCFS\n");
    printf("%d", current);

    for (i = 0; i < n; i++)
    {
        total += abs(current - request[i]);
        current = request[i];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void SSTF(int request[], int n, int head)
{
    int visited[100] = {0};
    int i, j, current = head;
    int min, pos, total = 0;

    printf("\nSSTF\n");
    printf("%d", current);

    for (i = 0; i < n; i++)
    {
        min = 9999;
        pos = -1;

        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0 &&
                abs(current - request[j]) < min)
            {
                min = abs(current - request[j]);
                pos = j;
            }
        }

        total += abs(current - request[pos]);
        current = request[pos];
        visited[pos] = 1;

        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void SCAN(int request[], int n, int head, int cylinders, int direction)
{
    int a[100];
    int i, current = head, total = 0;

    for (i = 0; i < n; i++)
        a[i] = request[i];

    sort(a, n);

    printf("\nSCAN\n");
    printf("%d", current);

    if (direction == 1)
    {
        for (i = 0; i < n; i++)
        {
            if (a[i] >= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }

        if (current != cylinders - 1)
        {
            total += abs(current - (cylinders - 1));
            current = cylinders - 1;
            printf(" -> %d", current);
        }

        for (i = n - 1; i >= 0; i--)
        {
            if (a[i] < head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }
    }
    else
    {
        for (i = n - 1; i >= 0; i--)
        {
            if (a[i] <= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }

        if (current != 0)
        {
            total += current;
            current = 0;
            printf(" -> %d", current);
        }

        for (i = 0; i < n; i++)
        {
            if (a[i] > head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void C_SCAN(int request[], int n, int head, int cylinders, int direction)
{
    int a[100];
    int i, current = head, total = 0;

    for (i = 0; i < n; i++)
        a[i] = request[i];

    sort(a, n);

    printf("\nC-SCAN\n");
    printf("%d", current);

    if (direction == 1)
    {
        for (i = 0; i < n; i++)
        {
            if (a[i] >= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }

        total += abs(current - (cylinders - 1));
        current = cylinders - 1;
        printf(" -> %d", current);

        total += cylinders - 1;
        current = 0;
        printf(" -> %d", current);

        for (i = 0; i < n; i++)
        {
            if (a[i] < head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }
    }
    else
    {
        for (i = n - 1; i >= 0; i--)
        {
            if (a[i] <= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }

        total += current;
        current = 0;
        printf(" -> %d", current);

        total += cylinders - 1;
        current = cylinders - 1;
        printf(" -> %d", current);

        for (i = n - 1; i >= 0; i--)
        {
            if (a[i] > head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void LOOK(int request[], int n, int head, int direction)
{
    int a[100];
    int i, current = head, total = 0;

    for (i = 0; i < n; i++)
        a[i] = request[i];

    sort(a, n);

    printf("\nLOOK\n");
    printf("%d", current);

    if (direction == 1)
    {
        for (i = 0; i < n; i++)
            if (a[i] >= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }

        for (i = n - 1; i >= 0; i--)
            if (a[i] < head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
    }
    else
    {
        for (i = n - 1; i >= 0; i--)
            if (a[i] <= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }

        for (i = 0; i < n; i++)
            if (a[i] > head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void C_LOOK(int request[], int n, int head, int direction)
{
    int a[100];
    int i, current = head, total = 0;

    for (i = 0; i < n; i++)
        a[i] = request[i];

    sort(a, n);

    printf("\nC-LOOK\n");
    printf("%d", current);

    if (direction == 1)
    {
        for (i = 0; i < n; i++)
            if (a[i] >= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }

        for (i = 0; i < n; i++)
            if (a[i] < head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
    }
    else
    {
        for (i = n - 1; i >= 0; i--)
            if (a[i] <= head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }

        for (i = n - 1; i >= 0; i--)
            if (a[i] > head)
            {
                total += abs(current - a[i]);
                current = a[i];
                printf(" -> %d", current);
            }
    }

    printf("\nTotal Head Movement = %d\n", total);
}
