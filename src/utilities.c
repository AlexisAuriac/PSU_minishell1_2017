/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Usefule functions.
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

void my_puterr(const char *str)
{
	if (str == NULL)
		return;
	write(STDERR_FILENO, str, my_strlen(str));
}

void safe_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
}

void free_tab(char **tab)
{
	if (tab == NULL)
		return;
	for (int i = 0 ; tab[i] ; ++i)
		free(tab[i]);
	free(tab);
}
