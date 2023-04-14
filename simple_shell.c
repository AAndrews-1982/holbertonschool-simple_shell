#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

/**
 * main - Simple shell program entry point.
 *
 * Return: 0 on success.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t child_pid;

    while (1)
    {
        printf("#cisfun$ ");
        if ((read = getline(&line, &len, stdin)) == -1)
            break;
        if ((child_pid = fork()) == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            char **argv = malloc(2 * sizeof(char *));
            if (argv == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            argv[0] = line;
            argv[1] = NULL;
            if (execve(line, argv, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
            break;
        }
        else
        {
            waitpid(child_pid, NULL, 0);
        }
    }
    free(line);
    exit(EXIT_SUCCESS);
}


