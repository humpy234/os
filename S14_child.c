//Q1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int a[20], n, i, j, temp, key;
    int low, high, mid;

    /* Child process after execve() */
    if (argc > 1 && argv[1][0] == 'C')
    {
        n = argc - 3;
        key = atoi(argv[argc - 1]);

        low = 0;
        high = n - 1;

        printf("\nChild Process\n");
        printf("Sorted Array: ");

        for (i = 0; i < n; i++)
            printf("%s ", argv[i + 2]);

        while (low <= high)
        {
            mid = (low + high) / 2;

            if (atoi(argv[mid + 2]) == key)
            {
                printf("\n%d found at position %d\n", key, mid + 1);
                return 0;
            }
            else if (atoi(argv[mid + 2]) < key)
                low = mid + 1;
            else
                high = mid - 1;
        }

        printf("\n%d not found\n", key);
        return 0;
    }

    /* Parent process */
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter item to search: ");
    scanf("%d", &key);

    /* Sort array */
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

    printf("Sorted Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    if (fork() == 0)
    {
        char *args[25];
        char nums[20][10], search[10];

        args[0] = argv[0];
        args[1] = "C";

        for (i = 0; i < n; i++)
        {
            sprintf(nums[i], "%d", a[i]);
            args[i + 2] = nums[i];
        }

        sprintf(search, "%d", key);
        args[n + 2] = search;
        args[n + 3] = NULL;

        execve(argv[0], args, NULL);

        perror("execve failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("\nParent Process Completed\n");
    }

    return 0;

}

//Q2
#include <stdio.h>

int main()
{
    int ref[] = {3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};
    int n = 15, f[10], frames, faults = 0;
    int i, j, pos = 0, found;

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

        /* Page fault */
        if (!found)
        {
            f[pos] = ref[i];
            pos = (pos + 1) % frames;
            faults++;
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
