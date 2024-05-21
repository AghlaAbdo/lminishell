/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/21 18:56:26 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"
#include "../parsing/parsing.h"

//!=========================
void prnt_rdr(t_rdr *head)
{
	printf("+------------------+---------+---------+\n");
	printf("|   File Name	   |  Mode   |  Flag   |\n");
	printf("+------------------+---------+---------+\n");
	t_rdr *current = head;

	while (current != NULL)
	{
		printf("| [%s]\t\t| %-8s| %-8d|\n", current->fl_name, current->mode, current->flag);
		current = current->next;
	}
	printf("+------------------+---------+---------+\n");
}
//!=========================

void	ft_parms_init(t_parms *holder, int ac, char *av[], char *ep[])
{
	(void)ac;
	(void)av;

	holder->pwd = getcwd(NULL, 0);
	holder->oldpwd = NULL;
	holder->ext_stts = 0;
	holder->envp = ep;
	holder->env = ft_env_crt(ep);
	holder->exprt_env = ft_env_dup(&holder->env);
	holder->n_file = 0;
	ft_env_rmv(&holder->exprt_env, "OLDPWD");
	ft_env_new(&holder->exprt_env, "OLDPWD", "");
	holder->exprt_env = ft_env_sort(&holder->exprt_env);
	ft_env_rmv(&holder->env, "OLDPWD");
}

char	*ft_line(int ext_stts, t_parms *param)
{
	char	*line;

	
	if (!ext_stts)
		line = readline("lminishell-0.1 ");
	else
		line = readline("\033[1;31m{🐚 \e[1;37mstatus:\e[0m 🚫\033[1;31m}>==$ \033[0m");
	if (!line)
		exit(param->ext_stts);
	if (line)
		add_history(line);
	return (line);
}

int	main(int ac, char *av[], char *ep[])
{
	t_parms	holder;
	char	*input;
	t_sh	*sh;

	ft_parms_init(&holder, ac, av, ep);
	while (1)
	{
		input = ft_line(holder.ext_stts, &holder);
		sh = ft_parser(input, &holder);
		//TODO shel = ft_parser(input, holder); //!PARSIG + error handling + explanding
		// sh = ft_exec_parser(input);
		// ft_exec(sh, &holder);
		// printf("\033[35m-------> Exit status : %d <-------\033[1;31m\n", holder.ext_stts);
		free(input);
	}
	//!============================================================================================

	printf("exit status = %d \n", holder.ext_stts);
	//!============================================================================================
	rl_clear_history(); //!ignore the error mark
	// atexit(z);
	ft_malloc(0, 1);
	return (0);
}
