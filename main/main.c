/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/27 16:04:37 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"
#include "../parsing/parsing.h"


//!=========================
void prnt_rdr(t_rdr *head)
{
	printf("+-------------------+---------+\n");
	printf("|   File Name	   |  Mode   |\n");
	printf("+-------------------+---------+\n");
	t_rdr *current = head;

	while (current != NULL)
	{
		printf("| %-17s| %-8s|\n", current->fl_name, current->mode);
		current = current->next;
	}
	printf("+-------------------+---------+\n");
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
void 	ft_handler(int sig)//!signal
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char *av[], char *ep[])
{
	t_parms	holder;
	char	*input;
	t_sh	*sh;

	rl_catch_signals = 0;//!signal
	signal(SIGINT, ft_handler);//!signal
	signal(SIGQUIT, SIG_IGN);//!signal
	ft_parms_init(&holder, ac, av, ep);
	while (1)
	{
		input = ft_line(&holder);
		sh = ft_parser(input, &holder);
		ft_exec(sh, &holder);
		free(input);
	}
	rl_clear_history();
	ft_malloc(0, 1);
	return (0);
}
