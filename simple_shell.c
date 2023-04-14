#include "shell.h"

#define PROMPT "#cisfun$ "

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int status = 1;

    while (status)
    {
        printf(PROMPT);
        read = getline(&line, &len, stdin);

        if (read == -1)
        {
            printf("\n");
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        pid_t child_pid;
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
            if (execve(line, NULL, NULL) == -1)
            {
                printf("Command not found\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}
