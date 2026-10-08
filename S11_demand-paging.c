//Q1
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
//Q2
#include <stdio.h>

int main()
{
    int ref[] = {8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};
    int n = 15, f[10], frames, faults = 0;
    int i, j, k, pos, far, found;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (i = 0; i < frames; i++)
        f[i] = -1;

    printf("\nPage\tFrames\t\tFault\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        /* Check if page is already present */
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

            /* Check for empty frame */
            for (j = 0; j < frames; j++)
                if (f[j] == -1)
                    break;

            if (j < frames)
                f[j] = ref[i];
            else
            {
                far = -1;
                pos = 0;

                /* Find page used farthest in future */
                for (j = 0; j < frames; j++)
                {
                    for (k = i + 1; k < n; k++)
                        if (f[j] == ref[k])
                            break;

                    if (k > far)
                    {
                        far = k;
                        pos = j;
                    }
                }

                f[pos] = ref[i];
            }
        }

        printf("%d\t", ref[i]);

        for (j = 0; j < frames; j++)
            printf("%d ", f[j]);

        printf("\t%s\n", found ? "No" : "Yes");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
}
