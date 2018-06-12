/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Changes directory.
*/

#include <stdlib.h>
#include "my.h"
#include "minishell1.h"

bool_t cd_home(char **env)
{
	int pos = get_var(env, "HOME");

	if (pos == -1 || chdir(env[pos] + 5)) {
		my_puterr("cd: Can't change to home directory.\n");
		return (FALSE);
	}
	else
		return (TRUE);
}

bool_t cd_back(char **env)
{
	int pos	= get_var(env, "OLDPWD");

	if (pos == -1 || chdir(env[pos] + 7)) {
		my_puterr(": No such file or directory.\n");
		return (FALSE);
	}
	else
		return (TRUE);
}

char **update_pwd(char **env, char *oldpwd)
{
	char pwd[1000] = "";
	char **set_pwd = my_malloc(sizeof(char *) * 4);

	getcwd(pwd, 999);
	set_pwd[0] = my_strdup("setenv");
	set_pwd[1] = my_strdup("PWD");
	set_pwd[2] = my_strdup(pwd);
	env = my_setenv(env, set_pwd);
	free(set_pwd[1]);
	free(set_pwd[2]);
	set_pwd[1] = my_strdup("OLDPWD");
	set_pwd[2] = my_strdup(oldpwd);
	env = my_setenv(env, set_pwd);
	free_tab(set_pwd);
	return (env);
}

char **my_cd(char **command, char **env)
{
	char oldpwd[1000] = "";
	bool_t success = FALSE;

	getcwd(oldpwd, 999);
	if (command[1] == NULL || !my_strcmp(command[1], "~"))
		success = cd_home(env);
	else if (!my_strcmp(command[1], "-"))
		success = cd_back(env);
	else if (error_cd(command))
		return (env);
	else
		success = !chdir(command[1]);
	if (success)
		env = update_pwd(env, oldpwd);
	return (env);
}
