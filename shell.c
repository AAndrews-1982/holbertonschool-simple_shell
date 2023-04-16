#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
 * main - A simple UNIX command line interpreter
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *path = "/bin/";
	char full_path[MAX_COMMAND_LENGTH];
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "Command: ", 9);
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		break;
	}
			command[strcspn(command, "\n")] = '\0';
			strcpy(full_path, path);
			strcat(full_path, command);
			status = access(full_path, X_OK);
	if (status == 0)
	{
			pid_t pid = fork();
		if (pid == 0)
		{
			execl(full_path, command, NULL);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			write(STDERR_FILENO, "Error: Fork failed\n", 19);
		}
	}
		else
			{
			write(STDERR_FILENO, "Error: Command not found\n", 25);
			}
		}
		return (0);
}
