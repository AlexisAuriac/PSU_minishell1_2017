/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Executes a shell command.
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "my.h"
#include "minishell1.h"

char **get_paths(char **env)
{
	char *path = NULL;
	char **bin_paths = NULL;

	for (int i = 0 ; env[i] ; ++i) {
		if (my_strncmp("PATH", env[i], 4) == 0) {
			path = env[i];
			break;
		}
	}
	if (path == NULL)
		return (NULL);
	bin_paths = my_str_split(path + 5, ':');
	return (bin_paths);
}

bool_t access_path(char **path, char *name, char **env)
{
	char **bin_paths = NULL;
	bool_t found = FALSE;

	*path = NULL;
	bin_paths = get_paths(env);
	if (bin_paths == NULL)
		return (FALSE);
	for (int i = 0 ; bin_paths[i] ; ++i) {
		bin_paths[i] = my_push_back(bin_paths[i], '/');
		bin_paths[i] = my_pushstr_back(bin_paths[i], name);
		if (access(bin_paths[i], X_OK) == 0) {
			found = TRUE;
			safe_free(*path);
			*path = bin_paths[i];
		}
		else
			free(bin_paths[i]);
	}
	free(bin_paths);
	return (found);
}

bool_t my_access(char **path, char *name, char **env)
{
	if (name == NULL)
		return (FALSE);
	else if (in_str('/', name)) {
		return (error_access(name));
	}
	else if (access_path(path, name, env))
		return (TRUE);
	else {
		my_puterr(name);
		my_puterr(": Command not found.\n");
		return (FALSE);
	}
}

int my_exec(char *path, char **command, char **env)
{
	pid_t son_pid = -1;
	int status = 0;

	son_pid = fork();
	if (son_pid == 0) {
		execve(path, command, env);
		exit(0);
	}
	waitpid(son_pid, &status, 0);
	if (status) {
		my_puterr(strsignal(status));
		my_puterr("\n");
	}
	if (path != command[0])
		free(path);
	return (0);
}
