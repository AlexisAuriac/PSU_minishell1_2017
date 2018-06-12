/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Displays environment variables and their values.
*/

#include "my.h"
#include "minishell1.h"

void my_env(char **env)
{
	if (env == NULL)
		return;
	for (int i = 0 ; env[i] ; ++i) {
		my_putstr(env[i]);
		write(1, "\n", 1);
	}
}

char **env_cpy(char **env1, char **env2)
{
	int i = 0;

	for (; env2[i] ; ++i) {
		env1[i] = my_strdup(env2[i]);
		if (env1[i] == NULL)
			return (NULL);
	}
	env1[i] = NULL;
	return (env1);
}

char **env_dup(char **env)
{
	char **new_env = NULL;
	int nb_var = 0;

	if (env == NULL)
		return (my_malloc(sizeof(char *) * 1));
	for (; env[nb_var] ; ++nb_var);
	new_env = my_malloc(sizeof(char *) * (nb_var + 1));
	if (new_env == NULL)
		return (NULL);
	if(env_cpy(new_env, env) == NULL)
		return (NULL);
	return (new_env);
}

int get_var(char **env, const char *name)
{
	int len = 0;

	if (env == NULL || name == NULL)
		return (-1);
	len = my_strlen(name);
	for (int i = 0 ; env[i] ; ++i) {
		if (my_strncmp(name, env[i], len) == 0 && env[i][len] == '=')
			return (i);
	}
	return (-1);
}
