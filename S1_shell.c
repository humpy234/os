  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX 100

void countFile(char option, char *filename)
{
    FILE *fp;
    int ch;
    long characters = 0, words = 0, lines = 0;
    int inWord = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;

        if (ch == '\n')
            lines++;

        if (isspace(ch))
        {
            inWord = 0;
        }
        else if (inWord == 0)
        {
            words++;
            inWord = 1;
        }
    }

    fclose(fp);

    switch (option)
    {
        case 'c':
            printf("Number of characters = %ld\n", characters);
            break;

        case 'w':
            printf("Number of words = %ld\n", words);
            break;

        case 'l':
            printf("Number of lines = %ld\n", lines);
            break;

        default:
            printf("Invalid count option\n");
            printf("Use: count c filename\n");
            printf("     count w filename\n");
            printf("     count l filename\n");
    }
}

int main()
{
    char command[100];
    char *args[MAX];
    int i;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        /* Read command */
        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        /* Remove newline */
        command[strcspn(command, "\n")] = '\0';

        /* Ignore empty command */
        if (strlen(command) == 0)
            continue;

        /* Tokenize command */
        i = 0;
        args[i] = strtok(command, " \t");

        while (args[i] != NULL && i < MAX - 1)
        {
            i++;
            args[i] = strtok(NULL, " \t");
        }

        /* Exit shell */
        if (strcmp(args[0], "exit") == 0)
            break;

        /* Implement count command */
        if (strcmp(args[0], "count") == 0)
        {
            if (i != 3)
            {
                printf("Usage: count c/w/l filename\n");
                continue;
            }

            countFile(args[1][0], args[2]);
            continue;
        }

        /* Create child process */
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
        }
        else if (pid == 0)
        {
            /* Child process executes command */
            execvp(args[0], args);

            /* execvp returns only if an error occurs */
            perror("Command not found");
            exit(1);
        }
        else
        {
            /* Parent waits for child */
            wait(NULL);
        }
    }

    return 0;



//Q1 menu driven
  #include <stdio.h>

int main()
{
    int allocation[5][3] = {
        {2, 3, 2},
        {4, 0, 0},
        {5, 0, 4},
        {4, 3, 3},
        {2, 2, 4}
    };

    int max[5][3] = {
        {9, 7, 5},
        {5, 2, 2},
        {1, 0, 4},
        {4, 4, 4},
        {6, 5, 5}
    };

    int available[3] = {3, 3, 2};
    int need[5][3];
    int choice, i, j;

    /* Calculate Need = Max - Allocation */
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 3; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    do
    {
        printf("\n===== BANKER'S ALGORITHM =====\n");
        printf("1. Accept Available\n");
        printf("2. Display Allocation and Max\n");
        printf("3. Display Need Matrix\n");
        printf("4. Display Available\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nEnter Available resources (A B C): ");
                scanf("%d %d %d",
                      &available[0],
                      &available[1],
                      &available[2]);

                printf("Available resources accepted.\n");
                break;

            case 2:
                printf("\nProcess\tAllocation\tMax\n");
                printf("\tA B C\t\tA B C\n");

                for (i = 0; i < 5; i++)
                {
                    printf("P%d\t", i);

                    for (j = 0; j < 3; j++)
                        printf("%d ", allocation[i][j]);

                    printf("\t\t");

                    for (j = 0; j < 3; j++)
                        printf("%d ", max[i][j]);

                    printf("\n");
                }
                break;

            case 3:
                printf("\nNeed Matrix (Max - Allocation)\n");
                printf("Process\tA B C\n");

                for (i = 0; i < 5; i++)
                {
                    printf("P%d\t", i);

                    for (j = 0; j < 3; j++)
                        printf("%d ", need[i][j]);

                    printf("\n");
                }
                break;

            case 4:
                printf("\nAvailable Resources:\n");
                printf("A\tB\tC\n");
                printf("%d\t%d\t%d\n",
                       available[0],
                       available[1],
                       available[2]);
                break;

            case 5:
                printf("\nProgram terminated.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}




  
}
