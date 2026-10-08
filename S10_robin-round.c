//Q1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process
{
    int pid, at, bt, rem, ct, wt, tat;
};

int main()
{
    struct Process p[20];
    int n, tq, i, time = 0, done = 0, run;
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nEnter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter first CPU burst of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        /* Generate next CPU burst randomly */
        p[i].bt += rand() % 5 + 1;

        p[i].rem = p[i].bt;
    }

    printf("\nGantt Chart:\n");

    while (done < n)
    {
        int executed = 0;

        for (i = 0; i < n; i++)
        {
            if (p[i].rem > 0 && p[i].at <= time)
            {
                executed = 1;

                run = (p[i].rem < tq) ? p[i].rem : tq;

                printf("| P%d ", p[i].pid);

                time += run;
                p[i].rem -= run;

                if (p[i].rem == 0)
                {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    avgwt += p[i].wt;
                    avgtat += p[i].tat;
                    done++;
                }
            }
        }

        if (!executed)
            time++;
    }

    printf("|\n");

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);

    return 0;
}
//Q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, req[50], head, i, j, temp;
    int total = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of requests: ");
    int r;
    scanf("%d", &r);

    printf("Enter disk request string:\n");
    for (i = 0; i < r; i++)
        scanf("%d", &req[i]);

    printf("Enter current head position: ");
    scanf("%d", &head);

    /* Sort requests */
    for (i = 0; i < r - 1; i++)
        for (j = i + 1; j < r; j++)
            if (req[i] > req[j])
            {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }

    printf("\nRequest Order: ");

    /* Move LEFT first */
    for (i = r - 1; i >= 0; i--)
    {
        if (req[i] < head)
        {
            printf("%d ", req[i]);
            total += abs(head - req[i]);
            head = req[i];
        }
    }

    /* Then reverse direction and move RIGHT */
    for (i = 0; i < r; i++)
    {
        if (req[i] > head)
        {
            printf("%d ", req[i]);
            total += abs(head - req[i]);
            head = req[i];
        }
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}
}
