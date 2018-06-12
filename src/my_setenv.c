/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Adds or midifies a environment variable.
*/

#include <stdlib.h>
#include "my.h"
#include "minishell1.h"

int overwrite_env_var(char **env, char *name, char *value)
{
	int pos = get_var(env, name);

	if (pos == -1)
		return (0);
	free(env[pos]);
	env[pos] = my_strdup(name);
	env[pos] = my_push_back(env[pos], '=');
	env[pos] = my_pushstr_back(env[pos], value);
	return (1);
}

char **add_env_var(char **env, char *name, char *value)
{
	char **copy = NULL;
	int nb_vars = 0;

	for (; env[nb_vars] ; ++nb_vars);
	copy = my_malloc(sizeof(char *) * (nb_vars + 2));
	if (copy == NULL)
		return (env);
	for (int i = 0 ; env[i] ; ++i)
		copy[i] = env[i];
	copy[nb_vars] = my_strdup(name);
	copy[nb_vars] = my_push_back(copy[nb_vars], '=');
	copy[nb_vars] = my_pushstr_back(copy[nb_vars], value);
	free(env);
	return (copy);
}

char **my_setenv(char **env, char **command)
{
	if (error_setenv(env, command))
		return (env);
	else if (overwrite_env_var(env, command[1], command[2]))
		return (env);
	else
		env = add_env_var(env, command[1], command[2]);
	return (env);
}
