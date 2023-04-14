#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PROMPT "#cisfun$ "
#define BUFSIZE 1024

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t child_pid;
    int status;

    while (1)
    {
        printf(PROMPT);
        fflush(stdout);
        if ((read = getline(&line, &len, stdin)) == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }
        line[strcspn(line, "\n")] = '\0'; /* Remove trailing newline */
        if ((child_pid = fork()) == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            char *argv[BUFSIZE];
            int argc = 0;
            char *token = strtok(line, " ");
            while (token != NULL && argc < BUFSIZE - 1)
            {
                argv[argc++] = token;
                token = strtok(NULL, " ");
            }
            argv[argc] = NULL;
            if (execve(argv[0], argv, NULL) == -1)
            {
                if (errno == ENOENT)
                {
                    printf("%s: command not found\n", argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0)
                {
                    printf("Command exited with status %d\n", exit_status);
                }
            }
            else if (WIFSIGNALED(status))
            {
                int signal_number = WTERMSIG(status);
                printf("Command terminated by signal %d\n", signal_number);
            }
        }
    }
    free(line);
    exit(EXIT_SUCCESS);
}