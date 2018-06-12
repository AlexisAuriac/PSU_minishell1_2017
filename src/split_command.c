/*
** EPITECH PROJECT, 2018
** minishell1
** File description:
** Splits a string command.
*/

#include <stdlib.h>
#include "my.h"
#include "minishell1.h"

static int is_end_word(const char current, const char next)
{
	if (current == ' ' || current == '\t')
		return (0);
	else if (next != ' ' && next != '\t' && next != '\0')
		return (0);
	return (1);
}

static int count_words(const char *str)
{
	int nb_word = 0;

	for (int i = 0 ; str[i] ; ++i) {
		if (is_end_word(str[i], str[i + 1]))
			++nb_word;
	}
	return (nb_word);
}

static int check_quot(const char *str)
{
	char quot = '\0';

	for (int i = 0 ; str[i] ; ++i) {
		if (str[i] == quot)
			quot = '\0';
		else if (!quot && (str[i] == '\"' || str[i] == '\''))
			quot = str[i];
	}
	if (quot) {
		my_puterr("Unmatched '");
		write(STDERR_FILENO, &quot, 1);
		my_puterr("'.\n");
		return (1);
	}
	return (0);
}

static char *get_word(const char **str)
{
	char *word = NULL;
	int wsize = 0;

	while ((*str)[0] == ' ' || (*str)[0] == '\t')
		++(*str);
	while ((*str)[wsize] != ' ' && (*str)[wsize] != '\t' && (*str)[wsize])
		++wsize;
	word = malloc(sizeof(char) * (wsize + 1));
	my_strncpy(word, *str, wsize);
	word[wsize] = '\0';
	(*str) += wsize;
	return (word);
}

char **split_command(const char *str)
{
	int nb_word = 0;
	char **split_str = NULL;

	if (str == NULL)
		return (NULL);
	if (check_quot(str))
		return (my_malloc(sizeof(char *)));
	nb_word = count_words(str);
	split_str = malloc(sizeof(char *) * (nb_word + 1));
	for (int i = 0 ; i < nb_word ; ++i)
		split_str[i] = get_word(&str);
	split_str[nb_word] = NULL;
	return (split_str);
}
