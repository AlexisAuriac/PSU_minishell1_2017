/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Gets commands from stdin.
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "minishell1.h"

void show_prompt(int tty)
{
	char path[1000] = "";
	int offset = 0;

	if (!tty)
		return;
	getcwd(path, 999);
	offset = my_strlen(path);
	while (path[offset] != '/' && offset != 0)
		--offset;
	write(STDOUT_FILENO, "(minishell1 ", 12);
	my_putstr(path + offset + 1);
	write(STDOUT_FILENO, ")$ ", 3);
}

char *get_next_command(char *buffer)
{
	int next = -1;

	next = my_str_seek(buffer, "&&");
	if (next >= 0) {
		buffer[next - 1] = '\0';
		return (my_strdup(buffer + next + 1));
	}
	next = my_str_seek(buffer, ";");
	if (next >= 0) {
		buffer[next] = '\0';
		return (my_strdup(buffer + next + 1));
	}
	return (NULL);
}

char **get_command(int tty)
{
	char *buffer = NULL;
	char **command = NULL;
	static char *next_command = NULL;

	if (next_command != NULL) {
		buffer = next_command;
		next_command = NULL;
	} else {
		show_prompt(tty);
		buffer = get_next_line(STDIN_FILENO);
		if (buffer == NULL)
			return (NULL);
	}
	if (buffer == NULL) {
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	next_command = get_next_command(buffer);
	command = split_command(buffer);
	free(buffer);
	return (command);
}

int do_command(char **command, char ***env)
{
	char *path = command[0];

	if (my_strcmp(command[0], "cd") == 0)
		*env = my_cd(command, *env);
	else if (my_strcmp(command[0], "env") == 0)
		my_env(*env);
	else if (my_strcmp(command[0], "setenv") == 0)
		*env = my_setenv(*env, command);
	else if (my_strcmp(command[0], "unsetenv") == 0)
		*env = my_unsetenv(*env, command);
	else if (my_access(&path, command[0], *env) == TRUE)
		my_exec(path, command, *env);
	return (0);
}
