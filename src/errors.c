/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Handles error cases for various functions.
*/

#include <sys/stat.h>
#include <dirent.h>
#include "my.h"
#include "minishell1.h"

bool_t error_access(char *name)
{
	DIR *dir = NULL;

	if (access(name, F_OK)) {
		my_puterr(name);
		my_puterr(": Command not found.\n");
		return (FALSE);
	}
	dir = opendir(name);
	if (access(name, X_OK) || dir != NULL) {
		if (dir != NULL)
			closedir(dir);
		my_puterr(name);
		my_puterr(": Permission denied.\n");
		return (FALSE);
	}
	return (TRUE);
}

bool_t error_cd(char **command)
{
	int nb_arg = 0;
	struct stat s;

	for (; command[nb_arg] ; ++nb_arg);
	if (nb_arg > 2) {
		my_puterr("cd: Too many arguments.\n");
		return (TRUE);
	}
	else if (stat(command[1], &s)) {
		my_puterr(command[1]);
		my_puterr(": No such file or directory.\n");
		return (TRUE);
	}
	else if (!S_ISDIR(s.st_mode)) {
		my_puterr(command[1]);
		my_puterr(": Not a directory.\n");
		return (TRUE);
	}
	return (FALSE);
}

bool_t error_setenv(char **env, char **command)
{
	int argc = 0;

	for (; command[argc] ; ++argc);
	if (argc == 1) {
		my_env(env);
		return (TRUE);
	}
	else if (argc > 3) {
		my_puterr("setenv: Too many arguments.\n");
		return (TRUE);
	}
	else if (!in_str(command[1][0], ALLOW) && !in_str(command[1][0], ALUP)) {
		my_puterr("setenv: Variable name must begin with a letter.\n");
		return (TRUE);
	}
	else if (my_str_is(command[1], IS_ALNUM) == FALSE) {
		my_puterr("setenv: Variable ");
		my_puterr("name must contain alphanumeric characters.\n");
		return (TRUE);
	}
	return (FALSE);
}
