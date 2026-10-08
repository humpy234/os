//Q1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process
{
    int pid, at, bt, ct, wt, tat;
};

int main()
{
    struct Process p[20], temp;
    int n, i, j, time = 0, done = 0, pos;
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter first CPU burst of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        /* Generate next CPU burst randomly */
        p[i].bt += rand() % 5 + 1;
        p[i].ct = 0;
    }

    printf("\nGantt Chart:\n");

    while (done < n)
    {
        pos = -1;

        /* Find shortest arrived process */
        for (i = 0; i < n; i++)
        {
            if (p[i].ct == 0 && p[i].at <= time)
            {
                if (pos == -1 || p[i].bt < p[pos].bt)
                    pos = i;
            }
        }

        if (pos == -1)
        {
            time++;
            continue;
        }

        printf("| P%d ", p[pos].pid);

        time += p[pos].bt;
        p[pos].ct = time;

        p[pos].tat = p[pos].ct - p[pos].at;
        p[pos].wt = p[pos].tat - p[pos].bt;

        avgwt += p[pos].wt;
        avgtat += p[pos].tat;
        done++;
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
    int req[] = {15, 30, 55, 90, 125, 140, 170};
    int r = 7, head = 100;
    int i, j, temp, total = 0;

    /* Sort requests */
    for (i = 0; i < r - 1; i++)
        for (j = i + 1; j < r; j++)
            if (req[i] > req[j])
            {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }

    printf("Request Order: ");

    /* Direction: Left */
    for (i = r - 1; i >= 0; i--)
    {
        if (req[i] < head)
        {
            printf("%d ", req[i]);
            total += abs(head - req[i]);
            head = req[i];
        }
    }

    /* Reverse direction */
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
