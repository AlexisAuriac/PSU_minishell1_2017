/*
** EPITECH PROJECT, 2017
** minishell1
** File description:
** Contains the prototypes of the project's functions.
*/

#ifndef MINISHELL1_H
#define MINISHELL1_H

#include "const.h"
#include "struct.h"
#include "macro.h"

//prompt.c
void show_prompt(int tty);
char **get_command(int tty);
int do_command(char **command, char ***env);

//errors.c
bool_t error_access(char *name);
bool_t error_cd(char **command);
bool_t error_setenv(char **env, char **command);

//my_cd.c
char **my_cd(char **command, char **env);

//my_env.c
void my_env(char **envp);
char **env_cpy(char **env1, char **env2);
char **env_dup(char **env);
int get_var(char **env, const char *name);

//my_setenv.c
char **my_setenv(char **env, char **command);

//my_unsetenv.c
char **my_unsetenv(char **env, char **command);

//my_exec.c
bool_t my_access(char **path, char *name, char **env);
int my_exec(char *path, char **command, char **env);

//utilities.c
void my_puterr(const char *str);
void safe_free(void *ptr);
void free_tab(char **tab);

//split_command.c
char **split_command(const char *str);

#endif
