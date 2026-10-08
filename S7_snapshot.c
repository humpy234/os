//Q1
#include <stdio.h>

#define P 5
#define R 4

int main()
{
    int allocation[P][R] = {
        {2, 0, 0, 1},
        {3, 1, 2, 1},
        {2, 1, 0, 3},
        {1, 3, 1, 2},
        {1, 4, 3, 2}
    };

    int max[P][R] = {
        {4, 2, 1, 2},
        {5, 2, 5, 2},
        {2, 3, 1, 6},
        {1, 4, 2, 4},
        {3, 6, 6, 5}
    };

    int available[R] = {3, 3, 2, 1};

    int need[P][R];
    int work[R];
    int finish[P] = {0};
    int safe[P];

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

    /* Display Allocation Matrix */
    printf("\nAllocation Matrix:\n");
    printf("       A B C D\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d     ", i);

        for (j = 0; j < R; j++)
        {
            printf("%d ", allocation[i][j]);
        }

        printf("\n");
    }

    /* Display Max Matrix */
    printf("\nMax Matrix:\n");
    printf("       A B C D\n");

    for (i = 0; i < P; i++)
    {
        printf("P%d     ", i);

        for (j = 0; j < R; j++)
        {
            printf("%d ", max[i][j]);
        }

        printf("\n");
    }

    /* Display Available */
    printf("\nAvailable:\n");
    printf("A B C D\n");
    printf("%d %d %d %d\n",
           available[0],
           available[1],
           available[2],
           available[3]);

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

    /* Copy Available to Work */
    for (j = 0; j < R; j++)
    {
        work[j] = available[j];
    }

    /*
     * Banker's Safety Algorithm
     */
    while (count < P)
    {
        found = 0;

        for (i = 0; i < P; i++)
        {
            if (finish[i] == 0)
            {
                int canRun = 1;

                /* Check Need <= Work */
                for (j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun)
                {
                    printf("\nP%d can execute.", i);

                    /* Release allocated resources */
                    for (j = 0; j < R; j++)
                    {
                        work[j] = work[j] + allocation[i][j];
                    }

                    safe[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;

                    printf("\nWork after P%d finishes: ", i);

                    for (j = 0; j < R; j++)
                    {
                        printf("%d ", work[j]);
                    }
                }
            }
        }

        if (found == 0)
            break;
    }

    /* Check whether system is safe */
    if (count == P)
    {
        printf("\n\nSystem is in SAFE STATE.\n");

        printf("Safe Sequence: ");

        for (i = 0; i < P; i++)
        {
            printf("P%d", safe[i]);

            if (i != P - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\n\nSystem is NOT in SAFE STATE.\n");
    }

    return 0;

}


//Q2
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    pid_t pid;
    int priority;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        /* Child process */
        priority = nice(-5);

        if (priority == -1 && errno != 0)
        {
            perror("nice failed");
        }
        else
        {
            printf("Child process\n");
            printf("Child PID: %d\n", getpid());
            printf("Child nice value: %d\n", priority);
        }
    }
    else
    {
        /* Parent process */
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(NULL);
    }

    return 0;
}
}
