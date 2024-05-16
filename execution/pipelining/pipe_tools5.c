/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:59:00 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/14 19:31:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_fds_collector(t_parms *param, int leng, int norm_i)
{
	if (param->ppc_idx == 0)
	{
		while (++norm_i < leng)
		{
			if (norm_i != param->ppc_idx)
				ft_norm_close(param->pp_chain, norm_i);
		}
	}
	else if (param->ppc_idx != 0 && param->ppc_idx != leng)
	{
		while (++norm_i < leng)
		{
			if (norm_i != param->ppc_idx && norm_i != param->ppc_idx - 1)
				ft_norm_close(param->pp_chain, norm_i);
		}
	}
	else if (param->ppc_idx == leng)
	{
		while (++norm_i < leng)
		{
			if (norm_i != leng - 1)
				ft_norm_close(param->pp_chain, norm_i);
		}
	}
}

int	ft_is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "env")
			|| !ft_strcmp(cmd, "pwd")
			|| !ft_strcmp(cmd, "echo")
			|| !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "exit")
			|| !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "unset"));
}

void	ft_norm_dclose(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	ft_norm_nfound_cmd(t_sh *curr_sh)
{
	write(2, curr_sh->value[0], ft_len(curr_sh->value[0]));
	write(2, ": command not found\n", 21);
	exit(WEXITSTATUS(errno));
}

