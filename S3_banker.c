//Q1
#include <stdio.h>

#define P 5
#define R 4

int main()
{
    int allocation[P][R] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };

    int max[P][R] = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };

    int available[R] = {1, 5, 2, 0};

    int need[P][R];
    int work[R];
    int finish[P] = {0};
    int safeSequence[P];

    int i, j, count = 0;
    int found;

    /* Calculate Need Matrix */
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    /* Display Need Matrix */
    printf("\nNeed Matrix:\n");
    printf("       A B C D\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d     ", i);

        for (j = 0; j < R; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    /* Initialize Work = Available */
    for (j = 0; j < R; j++)
    {
        work[j] = available[j];
    }

    /*
     * Banker's Algorithm
     */
    while (count < P)
    {
        found = 0;

        for (i = 0; i < P; i++)
        {
            if (finish[i] == 0)
            {
                /* Check Need <= Work */
                int possible = 1;

                for (j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if (possible)
                {
                    /*
                     * Process can execute.
                     * Work = Work + Allocation
                     */
                    for (j = 0; j < R; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    /* Check safe state */
    if (count == P)
    {
        printf("\nSystem is in SAFE STATE.\n");

        printf("Safe Sequence: ");

        for (i = 0; i < P; i++)
        {
            printf("P%d", safeSequence[i]);

            if (i != P - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in a safe state.\n");
    }

    return 0;
  
}




//Q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, req, head;
    int i, j;
    int totalMovement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of disk requests: ");
    scanf("%d", &req);

    int request[req];
    int visited[req];

    printf("Enter disk request string:\n");
    for (i = 0; i < req; i++)
    {
        scanf("%d", &request[i]);

        if (request[i] < 0 || request[i] >= n)
        {
            printf("Invalid request: %d\n", request[i]);
            return 1;
        }

        visited[i] = 0;
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= n)
    {
        printf("Invalid head position.\n");
        return 1;
    }

    printf("\nOrder of requests served:\n");
    printf("%d", head);

    /*
     * SSTF Algorithm
     * Select the unvisited request having the
     * shortest distance from the current head.
     */
    for (i = 0; i < req; i++)
    {
        int shortest = 999999;
        int index = -1;

        for (j = 0; j < req; j++)
        {
            if (visited[j] == 0)
            {
                int distance = abs(request[j] - head);

                if (distance < shortest)
                {
                    shortest = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;

        totalMovement += abs(request[index] - head);
        head = request[index];

        printf(" -> %d", head);
    }

    printf("\n\nTotal head movement = %d cylinders\n", totalMovement);

    return 0;
}
