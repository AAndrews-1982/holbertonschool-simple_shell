#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define PROMPT "$ "

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    int status;

    while (1)
    {
        pid_t pid;

        printf(PROMPT);
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            char *argv[2] = { NULL };
            argv[0] = command;

            if (execvp(argv[0], argv) == -1)
            {
                if (errno == ENOENT)
                {
                    printf("%s: command not found\n", command);
                }
                else
                {
                    perror("execvp");
                }
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}