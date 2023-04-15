#include "shell.h"

/**
 * main - Main function for the simple shell
 *
 * Return: 0 on success, otherwise an error code
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        prompt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            break; /* Exit on end-of-file (Ctrl+D) */
        }

        /* Remove the newline character from the command */
        line[read - 1] = '\0';

        /* Execute the command and check for errors */
        if (execute_command(line) == -1)
        {
            fprintf(stderr, "Error: command not found\n");
        }
    }

    free(line);

    return 0;
}

/**
 * prompt - Displays the shell prompt
 */
void prompt(void)
{
    printf("$ ");
    fflush(stdout);
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *command)
{
    pid_t pid;
    int status;
    char *path = "/bin/";
    char *full_path;
    char *argv[2];

    if ((pid = fork()) == 0)
    {
        /* Child process */
        full_path = malloc(strlen(path) + strlen(command) + 1);
        if (full_path == NULL)
        {
            perror("Error: malloc failed");
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, path);
        strcat(full_path, command);

        argv[0] = full_path;
        argv[1] = NULL;

        execve(full_path, argv, NULL);

        /* If execve returns, there was an error */
        perror(command);
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Forking error */
        perror("Error forking");
        return -1;
    }
    else
    {
        /* Parent process */
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Error waiting for child process");
            return -1;
        }
    }

    return 0;
}