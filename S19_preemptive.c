//Q1
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

//Q2#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

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
        printf("PID = %d\n", getpid());

        errno = 0;
        n = nice(-5);

        if (n == -1 && errno != 0)
            perror("nice");

        else
            printf("New Nice Value = %d\n", n);

        printf("Child has higher priority.\n");
    }
    else
    {
        printf("Parent Process\n");
        printf("PID = %d\n", getpid());

        wait(NULL);
        printf("Parent completed.\n");
    }

    return 0;
}
}
