//Q1
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, r, req[50], head, i, j, temp;
    int total = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of requests: ");
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

    /* Direction: Right */
    for (i = 0; i < r; i++)
    {
        if (req[i] >= head)
        {
            printf("%d ", req[i]);
            total += abs(head - req[i]);
            head = req[i];
        }
    }

    /* Reverse direction */
    for (i = r - 1; i >= 0; i--)
    {
        if (req[i] < head)
        {
            printf("%d ", req[i]);
            total += abs(head - req[i]);
            head = req[i];
        }
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}

//Q2
#include <stdio.h>

int main()
{
    int ref[] = {3,5,7,2,5,1,2,3,1,3,5,3,1,6,2};
    int n = 15, frames, f[10], count[10];
    int i, j, pos, found, faults = 0, time = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (i = 0; i < frames; i++)
    {
        f[i] = -1;
        count[i] = 0;
    }

    printf("\nPage\tFrames\t\tFault\n");

    for (i = 0; i < n; i++)
    {
        time++;
        found = 0;

        /* Check page in frames */
        for (j = 0; j < frames; j++)
        {
            if (f[j] == ref[i])
            {
                found = 1;
                count[j] = time;
                break;
            }
        }

        if (!found)
        {
            faults++;
            pos = -1;

            /* Find empty frame */
            for (j = 0; j < frames; j++)
            {
                if (f[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            /* Find LRU page */
            if (pos == -1)
            {
                pos = 0;
                for (j = 1; j < frames; j++)
                {
                    if (count[j] < count[pos])
                        pos = j;
                }
            }

            f[pos] = ref[i];
            count[pos] = time;
        }

        printf("%d\t", ref[i]);

        for (j = 0; j < frames; j++)
            printf("%d ", f[j]);

        printf("\t\t%s\n", found ? "No" : "Yes");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
}
