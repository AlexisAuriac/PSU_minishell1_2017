/*
** EPITECH PROJECT, 2017
** minishell1
** File description:
** Main file.
*/

#include <signal.h>
#include <wait.h>
#include "my.h"
#include "minishell1.h"

void sigint_hdl(int signum __attribute__((unused)))
{
	int status = 0;

	waitpid(-1, &status, 0);
	write(1, "\n", 1);
	if (!WIFSIGNALED(status))
		show_prompt(1);
}

int minishell1(char ***env)
{
	int stop = 0;
	char **command = NULL;
	int tty = isatty(STDIN_FILENO);

	while (!stop) {
		command = get_command(tty);
		if (command == NULL || my_strcmp(command[0], "exit") == 0) {
			if (tty)
				my_putstr("exit\n");
			if (command)
				stop = my_getnbr(command[1]);
			break;
		}
		stop = do_command(command, env);
		free_tab(command);
	}
	free_tab(command);
	return (stop);
}

int main(int ac __attribute__((unused)), char **av __attribute__((unused)),
	 char **envp)
{
	int status = 0;
	char **env = env_dup(envp);

	if (env == NULL)
		return (84);
	signal(SIGINT, &sigint_hdl);
	status = minishell1(&env);
	free_tab(env);
	return (status);
}
