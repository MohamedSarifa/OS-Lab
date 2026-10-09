#include <stdio.h>
#include "header.h"

int main()
{
    int choice;
    int cylinders, n, head, direction;
    int request[50];

    do
    {
        printf("\n==============================\n");
        printf("       DISK SCHEDULING\n");
        printf("==============================\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. LOOK\n");
        printf("6. C-LOOK\n");
        printf("7. Exit\n");
        printf("==============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6)
        {
            printf("\nEnter number of cylinders: ");
            scanf("%d", &cylinders);

            printf("Enter number of requests: ");
            scanf("%d", &n);

            printf("Enter request queue:\n");

            for (int i = 0; i < n; i++)
            {
                scanf("%d", &request[i]);
            }

            printf("Enter initial head position: ");
            scanf("%d", &head);

            /* Direction for all algorithms */
            printf("\nEnter direction:\n");
            printf("1. Right\n");
            printf("2. Left\n");
            printf("Enter your direction: ");
            scanf("%d", &direction);

            if (direction == 1)
            {
                direction = 1;       /* Right */
            }
            else if (direction == 2)
            {
                direction = 0;       /* Left */
            }
            else
            {
                printf("\nInvalid direction!\n");
                continue;
            }

            switch (choice)
            {
                case 1:
                    FCFS(request, n, head);
                    break;

                case 2:
                    SSTF(request, n, head);
                    break;

                case 3:
                    SCAN(request, n, head, cylinders, direction);
                    break;

                case 4:
                    C_SCAN(request, n, head, cylinders, direction);
                    break;

                case 5:
                    LOOK(request, n, head, direction);
                    break;

                case 6:
                    C_LOOK(request, n, head, direction);
                    break;
            }
        }
        else if (choice == 7)
        {
            printf("\nProgram terminated.\n");
        }
        else
        {
            printf("\nInvalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}
