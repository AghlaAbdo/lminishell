/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:29:07 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/14 19:16:39 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_norm_dup2_in(t_sh *curr_sh, t_parms *param)
{
		if (curr_sh->in_fd == -1)
		{
			if (dup2(param->pp_chain[param->ppc_idx - 1][0], STDIN_FILENO) == -1)
				ft_perror("pipe's read");
		}
		else
		{
			if (dup2(curr_sh->in_fd, STDIN_FILENO) == -1)
				ft_perror("pipe's read");
		}
}

void	ft_norm_dup2_out(t_sh *curr_sh, t_parms *param)
{
	if (curr_sh->out_fd == -1)
	{
		if (dup2(param->pp_chain[param->ppc_idx][1], STDOUT_FILENO) == -1)
			ft_perror("pipe's write");
	}
	else
	{
		if (dup2(curr_sh->out_fd, STDOUT_FILENO) == -1)
			ft_perror("pipe's write");
	}
}
