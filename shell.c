#include "shell.h"

/**
 * main - shell entry point
 *
 * Return: 0 on success
 */

int main(void)
{
		char *buffer = NULL, **args = NULL;
		size_t bufsize = 0;
		ssize_t read_bytes = 0;

		while (1)
	{
		printf("$ ");
		read_bytes = getline(&buffer, &bufsize, stdin);
	if (read_bytes == -1)
	{
	free(buffer);
	printf("\n");
		exit(EXIT_SUCCESS);
	}
	args = tokenize(buffer);
	execute(args);
	free(args);
	}
	free(buffer);
	return (0);
}

/**
 * tokenize - tokenize input string
 * @str: input string
 *
 * Return: array of pointers to tokens
 */

char **tokenize(char *str)
{
		char *token = NULL;
		char **tokens = malloc(sizeof(char *) * TOKEN_BUFSIZE);
		size_t i = 0;

	if (!tokens)
	{
	fprintf(stderr, "Allocation error\n");
	exit(EXIT_FAILURE);
	}

	token = strtok(str, TOKEN_DELIMITERS);
	while (token != NULL)
	{
	tokens[i] = token;
	i++;
	token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute - execute command
 * @args: array of pointers to tokens
 *
 * Return: 0 on success, 1 on error
 */

int execute(char **args)
{
	pid_t pid = 0;
	int status = 0;

	if (args[0] == NULL)
	return (1);

	pid = fork();
	if (pid == 0)
	{
	if (execvp(args[0], args) == -1)
{
		perror("Error");
		exit(EXIT_FAILURE);
		{
	}
	else if (pid < 0)
	{
	perror("Error");
	exit(EXIT_FAILURE);
	}
	else
	{
	do{
		waitpid(pid, &status, WUNTRACED);
	}
	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}
