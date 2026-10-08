//Q1
#include <stdio.h>

int main()
{
    int n, pages, i, j;
    int pageFaults = 0;
    int pointer = 0;
    int found;

    int reference[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};

    pages = sizeof(reference) / sizeof(reference[0]);

    printf("Enter number of frames: ");
    scanf("%d", &n);

    int frame[n];

    /* Initially all frames are empty */
    for (i = 0; i < n; i++)
        frame[i] = -1;

    printf("\nPage\tFrames\t\tStatus\n");
    printf("----------------------------------\n");

    for (i = 0; i < pages; i++)
    {
        found = 0;

        /* Check whether page is already present */
        for (j = 0; j < n; j++)
        {
            if (frame[j] == reference[i])
            {
                found = 1;
                break;
            }
        }

        /* Page fault */
        if (found == 0)
        {
            frame[pointer] = reference[i];
            pointer = (pointer + 1) % n;
            pageFaults++;
        }

        printf("%d\t", reference[i]);

        for (j = 0; j < n; j++)
        {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        if (found == 0)
            printf("\tPage Fault");
        else
            printf("\tHit");

        printf("\n");
    }

    printf("\nTotal number of pages = %d", pages);
    printf("\nTotal number of page faults = %d\n", pageFaults);

    return 0;
}


//Q2
#include <stdio.h>

#define MAX_P 20
#define MAX_R 20

int main()
{
    int n, m;
    int total[MAX_R];
    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];
    int request[MAX_R];

    int i, j, process;
    int possible = 1;

    /* Accept number of processes and resources */
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    /* Accept total instances */
    printf("\nEnter total instances of each resource:\n");

    for (j = 0; j < m; j++)
    {
        printf("Resource R%d: ", j);
        scanf("%d", &total[j]);
    }

    /* Accept Allocation matrix */
    printf("\nEnter Allocation Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    /* Accept Max matrix */
    printf("\nEnter Maximum Requirement Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    /* Calculate Available */
    for (j = 0; j < m; j++)
    {
        int allocated = 0;

        for (i = 0; i < n; i++)
        {
            allocated += allocation[i][j];
        }

        available[j] = total[j] - allocated;
    }

    /* Calculate Need = Max - Allocation */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    /* Display Need Matrix */
    printf("\n========== NEED MATRIX ==========\n");

    printf("       ");
    for (j = 0; j < m; j++)
        printf("R%d  ", j);

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d     ", i);

        for (j = 0; j < m; j++)
        {
            printf("%d   ", need[i][j]);
        }

        printf("\n");
    }

    /* Display Available */
    printf("\nAvailable Resources:\n");

    for (j = 0; j < m; j++)
    {
        printf("R%d = %d  ", j, available[j]);
    }

    printf("\n");

    /* Accept process making request */
    printf("\nEnter process number making the request (0-%d): ", n - 1);
    scanf("%d", &process);

    if (process < 0 || process >= n)
    {
        printf("Invalid process number.\n");
        return 1;
    }

    /* Accept request */
    printf("Enter resource request for P%d:\n", process);

    for (j = 0; j < m; j++)
    {
        printf("Request R%d: ", j);
        scanf("%d", &request[j]);
    }

    /*
     * Step 1:
     * Check Request <= Need
     */
    for (j = 0; j < m; j++)
    {
        if (request[j] > need[process][j])
        {
            possible = 0;
            printf("\nRequest exceeds the process's remaining need.\n");
            printf("Request cannot be granted.\n");
            return 0;
        }
    }

    /*
     * Step 2:
     * Check Request <= Available
     */
    for (j = 0; j < m; j++)
    {
        if (request[j] > available[j])
        {
            possible = 0;
            printf("\nResources are not currently available.\n");
            printf("Request cannot be granted immediately.\n");
            return 0;
        }
    }

    /*
     * Step 3:
     * Temporarily allocate the resources.
     */
    for (j = 0; j < m; j++)
    {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }

    /*
     * For immediate request checking, if both
     * Request <= Need and Request <= Available,
     * the request can be granted.
     */
    if (possible)
    {
        printf("\nRequest CAN be granted immediately.\n");

        printf("\nUpdated Available Resources:\n");

        for (j = 0; j < m; j++)
        {
            printf("R%d = %d  ", j, available[j]);
        }

        printf("\n");
    }

    return 0;
}
  
}
