//Q1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 50

struct File
{
    char name[20];
    int start;
    int length;
};

int main()
{
    int n;
    int bitVector[100];
    int freeBlocks[100];
    int freeCount = 0;

    struct File directory[MAX_FILES];
    int fileCount = 0;

    int i, j, choice;

    /* Random number generator */
    srand(time(NULL));

    printf("Enter number of disk blocks: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    /*
     * Randomly mark blocks as allocated/free.
     * 0 = Free
     * 1 = Allocated
     */
    for (i = 0; i < n; i++)
    {
        bitVector[i] = rand() % 2;
    }

    /* Create free block list */
    for (i = 0; i < n; i++)
    {
        if (bitVector[i] == 0)
        {
            freeBlocks[freeCount] = i;
            freeCount++;
        }
    }

    while (1)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("==========================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                /* Show Bit Vector */
                printf("\nBit Vector:\n");

                for (i = 0; i < n; i++)
                {
                    printf("%d ", bitVector[i]);

                    if ((i + 1) % 10 == 0)
                        printf("\n");
                }

                printf("\n");

                break;

            case 2:
            {
                char filename[20];
                int blocksRequired;
                int start = -1;

                printf("\nEnter file name: ");
                scanf("%s", filename);

                printf("Enter number of blocks required: ");
                scanf("%d", &blocksRequired);

                if (blocksRequired <= 0 || blocksRequired > n)
                {
                    printf("Invalid number of blocks.\n");
                    break;
                }

                if (fileCount >= MAX_FILES)
                {
                    printf("Directory is full.\n");
                    break;
                }

                /*
                 * Find consecutive free blocks.
                 * This is the main feature of
                 * sequential allocation.
                 */
                for (i = 0; i <= n - blocksRequired; i++)
                {
                    int found = 1;

                    for (j = 0; j < blocksRequired; j++)
                    {
                        if (bitVector[i + j] != 0)
                        {
                            found = 0;
                            break;
                        }
                    }

                    if (found)
                    {
                        start = i;
                        break;
                    }
                }

                if (start == -1)
                {
                    printf("No sufficient contiguous free blocks available.\n");
                    break;
                }

                /* Allocate consecutive blocks */
                for (i = start; i < start + blocksRequired; i++)
                {
                    bitVector[i] = 1;
                }

                /* Store file information */
                strcpy(directory[fileCount].name, filename);
                directory[fileCount].start = start;
                directory[fileCount].length = blocksRequired;

                fileCount++;

                /*
                 * Rebuild free block list
                 */
                freeCount = 0;

                for (i = 0; i < n; i++)
                {
                    if (bitVector[i] == 0)
                    {
                        freeBlocks[freeCount++] = i;
                    }
                }

                printf("\nFile '%s' created successfully.\n", filename);
                printf("Starting block = %d\n", start);
                printf("Allocated blocks: ");

                for (i = start; i < start + blocksRequired; i++)
                {
                    printf("%d", i);

                    if (i < start + blocksRequired - 1)
                        printf(" -> ");
                }

                printf("\n");

                break;
            }

            case 3:
                /* Show Directory */
                printf("\n========== DIRECTORY ==========\n");

                if (fileCount == 0)
                {
                    printf("No files in directory.\n");
                }
                else
                {
                    printf("%-15s %-15s %-10s\n",
                           "File Name", "Starting Block", "Length");

                    for (i = 0; i < fileCount; i++)
                    {
                        printf("%-15s %-15d %-10d\n",
                               directory[i].name,
                               directory[i].start,
                               directory[i].length);
                    }
                }

                printf("===============================\n");

                break;

            case 4:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

//Q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, req, head;
    int i, j, temp;
    int totalMovement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of disk requests: ");
    scanf("%d", &req);

    int request[req];

    printf("Enter disk request string:\n");

    for (i = 0; i < req; i++)
    {
        scanf("%d", &request[i]);

        if (request[i] < 0 || request[i] >= n)
        {
            printf("Invalid request: %d\n", request[i]);
            return 1;
        }
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= n)
    {
        printf("Invalid head position.\n");
        return 1;
    }

    /* Sort the request array */
    for (i = 0; i < req - 1; i++)
    {
        for (j = i + 1; j < req; j++)
        {
            if (request[i] > request[j])
            {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    printf("\nOrder of requests served:\n");
    printf("%d", head);

    /*
     * C-SCAN, moving RIGHT.
     *
     * First serve all requests greater than head.
     */
    for (i = 0; i < req; i++)
    {
        if (request[i] >= head)
        {
            printf(" -> %d", request[i]);
            totalMovement += abs(request[i] - head);
            head = request[i];
        }
    }

    /*
     * Move to the end of the disk (199).
     */
    if (head != n - 1)
    {
        printf(" -> %d", n - 1);
        totalMovement += (n - 1) - head;
        head = n - 1;
    }

    /*
     * C-SCAN jumps from the end to the beginning.
     * This movement is counted in the total head movement.
     */
    printf(" -> 0");
    totalMovement += n - 1;
    head = 0;

    /*
     * Serve remaining requests from the beginning.
     */
    for (i = 0; i < req; i++)
    {
        if (request[i] < head)
        {
            printf(" -> %d", request[i]);
            totalMovement += request[i] - head;
            head = request[i];
        }
    }

    printf("\n\nTotal head movement = %d cylinders\n", totalMovement);

    return 0;
}

  
}
