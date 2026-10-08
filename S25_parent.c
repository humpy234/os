#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());

        sleep(5);

        printf("\nAfter parent terminates:\n");
        printf("Child PID = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());

        printf("Child process completed.\n");
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID = %d\n", getpid());

        sleep(2);

        printf("Parent process terminated.\n");
        exit(0);
    }

    return 0;
}

//Q2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void search(char type, char *file, char *pattern)
{
    FILE *fp;
    char line[200];
    int count = 0;

    fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        char *p = line;

        while ((p = strstr(p, pattern)) != NULL)
        {
            count++;

            if (type == 'f')
            {
                printf("First occurrence found: %s", p);
                fclose(fp);
                return;
            }

            if (type == 'a')
                printf("Occurrence found: %s", p);

            p++;
        }
    }

    if (type == 'c')
        printf("Number of occurrences = %d\n", count);
    else if (count == 0)
        printf("Pattern not found\n");

    fclose(fp);
}

int main()
{
    char command[200], *args[10];
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

        if (strcmp(args[0], "search") == 0)
        {
            if (args[1] && args[2] && args[3])
                search(args[1][0], args[2], args[3]);
            else
                printf("Usage: search f/a/c filename pattern\n");

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
