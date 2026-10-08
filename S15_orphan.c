//Q1
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());

        sleep(5);

        printf("\nAfter parent terminates:\n");
        printf("Child PID = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());

        printf("Child process completed.\n");
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID = %d\n", getpid());

        sleep(2);

        printf("Parent process terminated.\n");
        exit(0);
    }

    return 0;
}

//Q2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process
{
    int pid, at, bt, rem, priority;
    int ct, wt, tat;
};

int main()
{
    struct Process p[20];
    int n, i, time = 0, done = 0;
    int highest, prev = -1;
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nEnter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter first CPU burst of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        printf("Enter priority of P%d: ", i + 1);
        scanf("%d", &p[i].priority);

        /* Generate next CPU burst randomly */
        p[i].bt += rand() % 5 + 1;
        p[i].rem = p[i].bt;
    }

    printf("\nGantt Chart:\n");

    while (done < n)
    {
        highest = -1;

        /* Find highest priority arrived process */
        for (i = 0; i < n; i++)
        {
            if (p[i].rem > 0 && p[i].at <= time)
            {
                if (highest == -1 ||
                    p[i].priority < p[highest].priority)
                    highest = i;
            }
        }

        if (highest == -1)
        {
            time++;
            continue;
        }

        if (prev != highest)
        {
            printf("| P%d ", p[highest].pid);
            prev = highest;
        }

        p[highest].rem--;
        time++;

        if (p[highest].rem == 0)
        {
            p[highest].ct = time;
            p[highest].tat = p[highest].ct - p[highest].at;
            p[highest].wt = p[highest].tat - p[highest].bt;

            avgwt += p[highest].wt;
            avgtat += p[highest].tat;
            done++;
        }
    }

    printf("|\n");

    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].priority, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);

    return 0;
}
}
