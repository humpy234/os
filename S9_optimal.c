//Q1
#include <stdio.h>

int main()
{
    int ref[] = {8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};
    int n = 15, frames, f[10], faults = 0;
    int i, j, k, pos, farthest, found;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (i = 0; i < frames; i++)
        f[i] = -1;

    printf("\nPage\tFrames\t\tPage Fault\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < frames; j++)
        {
            if (f[j] == ref[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            faults++;

            /* Find empty frame */
            for (j = 0; j < frames; j++)
                if (f[j] == -1)
                    break;

            if (j < frames)
                f[j] = ref[i];
            else
            {
                farthest = -1;
                pos = 0;

                for (j = 0; j < frames; j++)
                {
                    for (k = i + 1; k < n; k++)
                        if (f[j] == ref[k])
                            break;

                    if (k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }

                f[pos] = ref[i];
            }
        }

        printf("%d\t", ref[i]);

        for (j = 0; j < frames; j++)
            printf("%d ", f[j]);

        printf("\t\t%s\n", found ? "No" : "Yes");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
//Q2
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
    int n, i, j, time = 0, completed = 0;
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

        /* Generate next CPU burst randomly */
        p[i].bt += rand() % 5 + 1;
    }

    /* Sort by arrival time */
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    printf("\nGantt Chart:\n");

    while (completed < n)
    {
        int pos = -1;

        /* Find shortest job among arrived processes */
        for (i = 0; i < n; i++)
        {
            if (p[i].ct == 0 && p[i].at <= time)
            {
                if (pos == -1 || p[i].bt < p[pos].bt)
                    pos = i;
            }
        }

        /* CPU is idle */
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
        completed++;
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
}
