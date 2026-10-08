//Q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i;
    int head, total_movement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter number of disk requests: ");
    int req;
    scanf("%d", &req);

    printf("Enter disk request string:\n");
    for (i = 0; i < req; i++)
    {
        scanf("%d", &requests[i]);

        if (requests[i] < 0 || requests[i] >= n)
        {
            printf("Invalid request: %d\n", requests[i]);
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

    printf("\nOrder of requests served:\n");
    printf("%d", head);

    /* FCFS: serve requests in the same order as given */
    for (i = 0; i < req; i++)
    {
        total_movement += abs(requests[i] - head);
        head = requests[i];

        printf(" -> %d", head);
    }

    printf("\n\nTotal head movement = %d cylinders\n", total_movement);

    return 0;
}




//Q1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FILES 50

struct File
{
    char name[20];
    int start;
    int length;
    int blocks[MAX_FILES];
};

int main()
{
    int n, i, choice;
    int bitVector[100];
    int freeBlocks[100];
    int freeCount;
    struct File directory[MAX_FILES];
    int fileCount = 0;

    srand(time(NULL));

    printf("Enter number of disk blocks: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    /*
     * Randomly allocate some blocks.
     * 0 = free, 1 = allocated
     */
    for (i = 0; i < n; i++)
    {
        bitVector[i] = rand() % 2;
    }

    /*
     * Maintain list of free blocks
     */
    freeCount = 0;

    for (i = 0; i < n; i++)
    {
        if (bitVector[i] == 0)
        {
            freeBlocks[freeCount++] = i;
        }
    }

    while (1)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("===========================\n");

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
                /* Create New File */
                char filename[20];
                int blocksRequired;
                int j;

                printf("\nEnter file name: ");
                scanf("%s", filename);

                printf("Enter number of blocks required: ");
                scanf("%d", &blocksRequired);

                if (blocksRequired <= 0)
                {
                    printf("Invalid number of blocks.\n");
                    break;
                }

                if (blocksRequired > freeCount)
                {
                    printf("Not enough free blocks available.\n");
                    break;
                }

                if (fileCount >= MAX_FILES)
                {
                    printf("Directory is full.\n");
                    break;
                }

                /*
                 * Allocate free blocks to the file.
                 * In linked allocation, each block points
                 * to the next block.
                 */
                strcpy(directory[fileCount].name, filename);
                directory[fileCount].start = freeBlocks[0];
                directory[fileCount].length = blocksRequired;

                for (j = 0; j < blocksRequired; j++)
                {
                    directory[fileCount].blocks[j] = freeBlocks[j];
                    bitVector[freeBlocks[j]] = 1;
                }

                /*
                 * Remove allocated blocks from free list
                 */
                for (j = blocksRequired; j < freeCount; j++)
                {
                    freeBlocks[j - blocksRequired] = freeBlocks[j];
                }

                freeCount -= blocksRequired;

                printf("\nFile '%s' created successfully.\n", filename);

                printf("Allocated blocks: ");

                for (j = 0; j < blocksRequired; j++)
                {
                    printf("%d", directory[fileCount].blocks[j]);

                    if (j < blocksRequired - 1)
                        printf(" -> ");
                }

                printf(" -> NULL\n");

                fileCount++;

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
                    printf("%-15s %-10s %-10s\n",
                           "File Name", "Start", "Blocks");

                    for (i = 0; i < fileCount; i++)
                    {
                        int j;

                        printf("%-15s %-10d ",
                               directory[i].name,
                               directory[i].start);

                        for (j = 0; j < directory[i].length; j++)
                        {
                            printf("%d", directory[i].blocks[j]);

                            if (j < directory[i].length - 1)
                                printf(" -> ");
                        }

                        printf("\n");
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
}
