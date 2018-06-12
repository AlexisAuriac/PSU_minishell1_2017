/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Unsets an environment variable.
*/

#include <stdlib.h>
#include "my.h"
#include "minishell1.h"

int del_env(char *name, char **env, int nb_vars)
{
	int len = my_strlen(name);

	for (int i = 0 ; i < nb_vars ; ++i) {
		if (my_strncmp(name, env[i], len) == 0 && env[i][len] == '=') {
			free(env[i]);
			env[i] = NULL;
			return (1);
		}
	}
	return (0);
}

char **my_unsetenv(char **env, char **command)
{
	char **copy = NULL;
	int nb_vars = 0;
	int unset = 0;

	if (command[1] == NULL) {
		my_puterr("unsetenv: Too few arguments.\n");
		return (env);
	}
	for (; env[nb_vars] ; ++nb_vars);
	for (int i = 1 ; command[i] ; ++i)
		unset += del_env(command[i], env, nb_vars);
	copy = my_malloc(sizeof(char *) * (nb_vars - unset + 1));
	if (copy == NULL)
		return (NULL);
	for (int i = 0, j = 0 ; j < nb_vars ; ++i, ++j) {
		while (env[j] == NULL && j < nb_vars) {
			++j;
		}
		copy[i] = env[j];
	}
	free(env);
	return (copy);
}
