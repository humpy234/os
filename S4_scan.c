//Q1
#include <stdio.h>

#define P 5
#define R 3

int main()
{
    int allocation[P][R];
    int max[P][R];
    int need[P][R];
    int available[R];

    int choice;
    int i, j;

    while (1)
    {
        printf("\n========== BANKER'S ALGORITHM ==========\n");
        printf("1. Accept Allocation and Max\n");
        printf("2. Accept Available\n");
        printf("3. Display Allocation and Max\n");
        printf("4. Find Need and Display It\n");
        printf("5. Display Available\n");
        printf("6. Exit\n");
        printf("=========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nEnter Allocation Matrix (A B C):\n");

                for (i = 0; i < P; i++)
                {
                    printf("P%d: ", i);
                    for (j = 0; j < R; j++)
                    {
                        scanf("%d", &allocation[i][j]);
                    }
                }

                printf("\nEnter Max Matrix (A B C):\n");

                for (i = 0; i < P; i++)
                {
                    printf("P%d: ", i);
                    for (j = 0; j < R; j++)
                    {
                        scanf("%d", &max[i][j]);
                    }
                }

                printf("\nAllocation and Max matrices accepted.\n");
                break;

            case 2:
                printf("\nEnter Available resources (A B C): ");
                for (j = 0; j < R; j++)
                {
                    scanf("%d", &available[j]);
                }

                printf("Available resources accepted.\n");
                break;

            case 3:
                printf("\n========== ALLOCATION MATRIX ==========\n");
                printf("       A  B  C\n");

                for (i = 0; i < P; i++)
                {
                    printf("P%d     ", i);

                    for (j = 0; j < R; j++)
                    {
                        printf("%d  ", allocation[i][j]);
                    }

                    printf("\n");
                }

                printf("\n========== MAX MATRIX ==========\n");
                printf("       A  B  C\n");

                for (i = 0; i < P; i++)
                {
                    printf("P%d     ", i);

                    for (j = 0; j < R; j++)
                    {
                        printf("%d  ", max[i][j]);
                    }

                    printf("\n");
                }

                break;

            case 4:
                /* Need = Max - Allocation */

                for (i = 0; i < P; i++)
                {
                    for (j = 0; j < R; j++)
                    {
                        need[i][j] =
                            max[i][j] - allocation[i][j];
                    }
                }

                printf("\n========== NEED MATRIX ==========\n");
                printf("       A  B  C\n");

                for (i = 0; i < P; i++)
                {
                    printf("P%d     ", i);

                    for (j = 0; j < R; j++)
                    {
                        printf("%d  ", need[i][j]);
                    }

                    printf("\n");
                }

                break;

            case 5:
                printf("\nAvailable Resources:\n");
                printf("A = %d\n", available[0]);
                printf("B = %d\n", available[1]);
                printf("C = %d\n", available[2]);

                break;

            case 6:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}


//Q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, req, head, direction;
    int i, j, temp;
    int totalMovement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of disk requests: ");
    scanf("%d", &req);

    int request[req];

    printf("Enter disk request string:\n");
    for (i = 0; i < req; i++)
    {
        scanf("%d", &request[i]);

        if (request[i] < 0 || request[i] >= n)
        {
            printf("Invalid request: %d\n", request[i]);
            return 1;
        }
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("Enter direction (0 = Left, 1 = Right): ");
    scanf("%d", &direction);

    if (head < 0 || head >= n)
    {
        printf("Invalid head position.\n");
        return 1;
    }

    /* Sort requests */
    for (i = 0; i < req - 1; i++)
    {
        for (j = i + 1; j < req; j++)
        {
            if (request[i] > request[j])
            {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    printf("\nOrder of requests served:\n");
    printf("%d", head);

    if (direction == 0)
    {
        /* Move LEFT first */

        /* Serve requests smaller than head */
        for (i = req - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                printf(" -> %d", request[i]);
                totalMovement += abs(head - request[i]);
                head = request[i];
            }
        }

        /*
         * Go to the left end of disk (0)
         * if there are requests on the right.
         */
        if (head != 0)
        {
            printf(" -> 0");
            totalMovement += head;
            head = 0;
        }

        /* Reverse direction and serve remaining requests */
        for (i = 0; i < req; i++)
        {
            if (request[i] > head)
            {
                printf(" -> %d", request[i]);
                totalMovement += abs(request[i] - head);
                head = request[i];
            }
        }
    }
    else
    {
        /* Move RIGHT first */

        /* Serve requests greater than head */
        for (i = 0; i < req; i++)
        {
            if (request[i] > head)
            {
                printf(" -> %d", request[i]);
                totalMovement += abs(request[i] - head);
                head = request[i];
            }
        }

        /*
         * Go to the right end of disk (n-1)
         * if there are requests on the left.
         */
        if (head != n - 1)
        {
            printf(" -> %d", n - 1);
            totalMovement += (n - 1) - head;
            head = n - 1;
        }

        /* Reverse direction and serve remaining requests */
        for (i = req - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                printf(" -> %d", request[i]);
                totalMovement += abs(head - request[i]);
                head = request[i];
            }
        }
    }

    printf("\n\nTotal head movement = %d cylinders\n", totalMovement);

    return 0;
}
Give
