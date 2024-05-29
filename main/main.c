/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 08:36:16 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"
#include "../parsing/parsing.h"
#include <signal.h>
#include <sys/signal.h>


//!=========================
void prnt_rdr(t_rdr *head)
{
	printf("+-------------------+---------+---------+\n");
	printf("|   File Name	   |  Mode   |  flag     |\n");
	printf("+-------------------+---------+---------+\n");
	t_rdr *current = head;

	while (current != NULL)
	{
		printf("| %-17s| %-8s|\t%d\n", current->fl_name, current->mode, current->flag);
		current = current->next;
	}
	printf("+-------------------+---------+---------+\n");
}
void prnt_sh(t_sh *head)
{
	printf("+-------------------+---------+\n");
	printf("|   CMD	   |  TYPE   |\n");
	printf("+-------------------+---------+\n");
	t_sh *current = head;

	while (current != NULL)
	{
		printf("| %-17s| %-8s|\n", current->value[0], current->type);
		current = current->next;
	}
	printf("+-------------------+---------+\n");
}

void prnt_env(t_env *head)
{
	printf("+-------------------+---------+\n");
	printf("|   key	   |  value   |\n");
	printf("+-------------------+---------+\n");
	t_env *current = head;

	while (current != NULL)
	{
		printf("| %-17s| %-8s|\n", current->key, current->value);
		current = current->next;
	}
	printf("+-------------------+---------+\n");
}
//!=========================

void	ft_parms_init(t_parms *holder, int ac, char *av[], char *ep[])
{
	char pwd[MAXPATHLEN];

	(void)ac;
	(void)av;
	getcwd(pwd, MAXPATHLEN);
	holder->pwd = pwd;
	holder->oldpwd = NULL;
	holder->ext_stts = 0;
	holder->envp = ep;
	holder->env = ft_env_crt(ep, 0);
	holder->exprt_env = ft_env_crt(ep, 1);
	holder->n_file = 0;
	ft_env_rmv(&holder->exprt_env, "OLDPWD");
	ft_env_new(&holder->exprt_env, "OLDPWD", "");
	holder->exprt_env = ft_env_sort(&holder->exprt_env);
	ft_env_rmv(&holder->env, "OLDPWD");
}

char	*ft_line(t_parms *param)
{
	char	*line;
	
	line = readline("lminishell-0.1$ ");
	if (!line)
	{
		printf("exit\n");
		exit(param->ext_stts);
	}
	if (line)
		add_history(line);
	return (line);
}

void	h2(int s)
{
	if (s == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_inchild = 1;
	}
}


int	main(int ac, char *av[], char *ep[])
{
	t_parms	holder;
	char	*input;
	t_sh	*sh;

	if (!isatty(0))
		return (1);
	g_inchild= 0;
	rl_catch_signals = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	ft_parms_init(&holder, ac, av, ep);
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, h2);
		input = ft_line(&holder);
		if (g_inchild)
			holder.ext_stts = 1;
		g_inchild = 0;
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		sh = ft_parser(input, &holder);
		g_inchild = 1;
		ft_exec(sh, &holder);
		g_inchild = 0;
		free(input);
	}
	rl_clear_history();
	ft_malloc(0, 1);
	return (0);
}
