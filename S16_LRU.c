//Q1
#include <stdio.h>

int main()
{
    int ref[] = {3,5,7,2,5,1,2,3,1,3,5,3,1,6,2};
    int n = 15, frames, f[10], counter[10];
    int i, j, pos, found, faults = 0, time = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (i = 0; i < frames; i++)
    {
        f[i] = -1;
        counter[i] = 0;
    }

    printf("\nPage\tFrames\t\tFault\n");

    for (i = 0; i < n; i++)
    {
        time++;
        found = 0;

        /* Check if page is already present */
        for (j = 0; j < frames; j++)
        {
            if (f[j] == ref[i])
            {
                counter[j] = time;
                found = 1;
                break;
            }
        }

        /* Page fault */
        if (!found)
        {
            faults++;

            /* Find empty frame */
            pos = -1;

            for (j = 0; j < frames; j++)
                if (f[j] == -1)
                {
                    pos = j;
                    break;
                }

            /* Find least recently used page */
            if (pos == -1)
            {
                pos = 0;

                for (j = 1; j < frames; j++)
                    if (counter[j] < counter[pos])
                        pos = j;
            }

            f[pos] = ref[i];
            counter[pos] = time;
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
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void count(char type, char *file)
{
    FILE *fp;
    int ch, characters = 0, words = 0, lines = 0;
    int inword = 0;

    fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;

        if (ch == '\n')
            lines++;

        if (ch == ' ' || ch == '\n' || ch == '\t')
            inword = 0;
        else if (inword == 0)
        {
            words++;
            inword = 1;
        }
    }

    fclose(fp);

    if (type == 'c')
        printf("Characters = %d\n", characters);
    else if (type == 'w')
        printf("Words = %d\n", words);
    else if (type == 'l')
        printf("Lines = %d\n", lines);
    else
        printf("Invalid count option\n");
}

int main()
{
    char command[100], *args[10];
    int i;

    while (1)
    {
        printf("$ ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        i = 0;
        args[i] = strtok(command, " ");

        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "count") == 0)
        {
            if (args[1] != NULL && args[2] != NULL)
                count(args[1][0], args[2]);
            else
                printf("Usage: count c/w/l filename\n");

            continue;
        }

        if (fork() == 0)
        {
            execvp(args[0], args);
            printf("Command not found\n");
            exit(1);
        }
        else
            wait(NULL);
    }

    return 0;
}
}
