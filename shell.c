#include "shell.h"

void tokenize_string(char *str, char *delims, char **tokens);
int create_child(char *call_path, char **str_arr);
int check_path(char **path_array, char **token_array);
void print_env(char **env);

/**
 * main - entry point
 * @argc: arg counter
 * @argv: array of args
 * @env: environment
 * Return: int
 */
int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	char *path = NULL;
	size_t size = 0;
	char *tokarr[20];
	char *patharr[20];
	int ret_value = 0;

	(void)argc;
	(void)argv;
	while (*env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = (*env + 5);
			break;
		}
		env++;
	}
	tokenize_string(path, ":", patharr);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&input, &size, stdin) == -1)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		tokenize_string(input, " \n\t", tokarr);

		if (!tokarr[0] || _strcmp(tokarr[0], "env") == 0)
			continue;
		if (_strcmp(tokarr[0], "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		if (access(tokarr[0], X_OK) == 0)
			create_child(tokarr[0], tokarr);
		else
			ret_value = check_path(patharr, tokarr);

	}
	return (ret_value);
}

/**
 * print_env - Prints the current environment.
 * @env: An array of strings representing the environment variables.
 *
 * Description: This function iterates through the environment variables
 * array and prints each variable followed by a newline character.
 */
void print_env(char **env)
{
	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * tokenize_string - tokenize a passed in string
 * @str: string to tokenize
 * @delims: deliminators
 * @tokens: the array to save the tokens
 * Return: void
 */
void tokenize_string(char *str, char *delims, char **tokens)
{
	char *path_token = strtok(str, delims);
	int i = 0;

	while (path_token != NULL)
	{
		tokens[i] = path_token;
		i++;
		path_token = strtok(NULL, delims);
	}
	tokens[i] = NULL;
}

/**
 * check_path - check if the path leads to a system call
 * @path_array: the string array containing the paths
 * @token_array: the string array of tokens
 * Return: int 127
 */
int check_path(char **path_array, char **token_array)
{
	int i = 0;
	char *comp_path = NULL;
	struct stat x;

	while (path_array[i] != NULL)
	{
		comp_path = malloc(_strlen(token_array[0]) + _strlen(path_array[i]) + 2);
		_strcpy(comp_path, path_array[i]);
		_strcat(comp_path, "/");
		_strcat(comp_path, token_array[0]);
		if (stat(comp_path, &x) == 0)
		{
			create_child(comp_path, token_array);
			free(comp_path);
			return (0);
		}
		free(comp_path);
		i++;
	}
	return (127);
}

/**
 * create_child - function to create child process
 * @call_path: path of system call
 * @str_arr: array of string
 * Return: int
 */
int create_child(char *call_path, char **str_arr)
{
	pid_t cop;
	int status = 0;

	cop = fork();
	if (cop == 0)
	{
		if (execve(call_path, str_arr, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (cop < 0)
		exit(EXIT_FAILURE);
	else
	{
		do {
			cop = waitpid(cop, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (status);
}
