/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/30 21:56:33 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"
#include "../parsing/parsing.h"

void	ft_parms_init(t_parms *holder, int ac, char *av[], char *ep[])
{
	char	pwd[MAXPATHLEN];

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

void	ft_norm_main(t_parms holder, t_sh *sh)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, fthandlert);
		input = ft_line(&holder);
		if (g_inchild)
			holder.ext_stts = 1;
		g_inchild = 0;
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
		sh = ft_parser(input, &holder);
		g_inchild = 1;
		holder.pp_chain = (int (*)[2])ft_pp_chain_creator(sh);
		ft_exec(sh, &holder, -1, -1);
		g_inchild = 0;
		free(input);
	}
}

int	main(int ac, char *av[], char *ep[])
{
	t_parms	holder;
	t_sh	*sh;

	if (!isatty(0))
		return (1);
	g_inchild = 0;
	rl_catch_signals = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	ft_parms_init(&holder, ac, av, ep);
	ft_norm_main(holder, sh);
	rl_clear_history();
	ft_malloc(0, 1);
	return (0);
}
