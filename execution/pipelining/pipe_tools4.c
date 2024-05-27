/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 09:15:52 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/26 19:25:18 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <stdio.h>

int	ft_pp_chain_len(t_sh *sh)
{
	int		i;
	int		pp_nbr;
	t_sh	*head;

	i = -1;
	head = sh;
	pp_nbr = 0;
	while (head)
	{
		if (ft_strcmp(head->type, "PIPE") == 0)
			pp_nbr++;
		head = head->next;
	}
	return (pp_nbr);
}

void	ft_norm_ext_stts(t_parms * param)
{
	int	ex_stts;
	
	close(param->child_stts[1]);
	read(param->child_stts[0], &ex_stts, sizeof(ex_stts));
	if (ex_stts == 127)
		param->ext_stts = 127;
	else if (ex_stts == 256)
		param->ext_stts = 1;
	else
	{
		if (param->ext_stts == 256)
			param->ext_stts = 1;
		else
			param->ext_stts = ex_stts;
	}
	close(param->child_stts[0]);
}

void	ft_norm_child_stts(t_sh *curr_sh, t_parms * param, int stts)
{
	(void)param;
	(void)stts;
	write(2, curr_sh->value[0], ft_len(curr_sh->value[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	ft_norm_err_msg(char **cmd, int errno_nbr, char *msg)
{
	if (errno_nbr == 14)
	{
		write(2, cmd[0], ft_len(cmd[0]));
		write(2, msg, ft_len(msg));
	}
	exit(errno_nbr);
}

int	(*ft_pp_chain_creator(t_sh *sh))[2]
{
	int		(*pp_chain)[2];
	int		pp_nbr;
	int		i;

	i = -1;
	pp_nbr = ft_pp_chain_len(sh);
	pp_chain = ft_malloc(pp_nbr * sizeof(int [2]), 0);
	while (++i < pp_nbr)
	{
		if (pipe(pp_chain[i]) == -1)
		{
			while (i >= 0)
			{
				close(pp_chain[i][0]);
				close(pp_chain[i][1]);
				i--;
			}
			free(pp_chain);
			perror("muli-pipe creation failed");
		}
	}
	return (pp_chain);
}
