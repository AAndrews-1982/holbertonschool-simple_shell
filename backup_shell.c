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
    char *trimmed_line; /* Move the declaration here */

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

        /* Trim spaces from the command */
        trimmed_line = trim_spaces(line);

        /* Execute the command and check for errors */
        if (execute_command(trimmed_line) == -1)
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
    char *path_env = getenv("PATH");
    char *path, *save_ptr, *full_path;
    char *argv[2];

    if ((pid = fork()) == 0)
    {
        /* Child process */
        argv[0] = command;
        argv[1] = NULL;

        if (strchr(command, '/') != NULL)
        {
            /* If command contains '/', try executing it directly */
            execve(command, argv, NULL);
        }
        else if (path_env != NULL)
        {
            path_env = strdup(path_env);

            /* Iterate over directories in PATH */
            path = strtok_r(path_env, ":", &save_ptr);
            while (path != NULL)
            {
                full_path = malloc(strlen(path) + strlen(command) + 2);
                if (full_path == NULL)
                {
                    perror("Error: malloc failed");
                    exit(EXIT_FAILURE);
                }

                strcpy(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, command);

                execve(full_path, argv, NULL);

                free(full_path);
                path = strtok_r(NULL, ":", &save_ptr);
            }

            free(path_env);
        }

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
