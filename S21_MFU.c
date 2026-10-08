#include <stdio.h>

int main()
{
    int ref[] = {8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};
    int n = 15, frames, f[10], freq[10];
    int i, j, pos, found, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (i = 0; i < frames; i++)
    {
        f[i] = -1;
        freq[i] = 0;
    }

    printf("\nPage\tFrames\t\tFault\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        /* Check if page is present */
        for (j = 0; j < frames; j++)
        {
            if (f[j] == ref[i])
            {
                found = 1;
                freq[j]++;
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

            /* Find Most Frequently Used page */
            if (pos == -1)
            {
                pos = 0;

                for (j = 1; j < frames; j++)
                {
                    if (freq[j] > freq[pos])
                        pos = j;
                }
            }

            f[pos] = ref[i];
            freq[pos] = 1;
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
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid, n;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());

        n = nice(-5);

        if (n == -1)
            perror("nice");
        else
            printf("New Nice Value = %d\n", n);

        printf("Child priority increased.\n");
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID = %d\n", getpid());

        wait(NULL);
        printf("Parent completed.\n");
    }

    return 0;
}

}
