/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:28:47 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:35:21 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <stdio.h>
#include <unistd.h>

static void	ft_norm_piperf(t_sh *sh, t_rdr *rdrs, t_parms *param)
{
	if (sh->out_fd == -1)
	{
		if (ft_is_dir(rdrs->fl_name) == 1)
			exit(1);
		if (access(rdrs->fl_name, W_OK) == -1)
			ft_redirs_bad_inf(rdrs, sh, param, errno);
		else
			ft_redirs_bad_inf(rdrs, sh, param, errno);
	}
}

static void	ft_norm_pipers(t_sh *sh, t_rdr *rdrs, t_parms *param)
{
	if (sh->in_fd == -1)
	{
		if (ft_is_dir(rdrs->fl_name) == 1)
			exit(1);
		if (access(rdrs->fl_name, R_OK) == -1)
		{
			ft_redirs_bad_inf(rdrs, sh, param, errno);
			exit(1);
		}
		else
			ft_redirs_bad_inf(rdrs, sh, param, errno);
	}
}

static void	ft_norm_pipert(t_sh *sh, t_rdr *rdrs, t_parms *param)
{
	if (sh->out_fd == -1)
	{
		if (ft_is_dir(rdrs->fl_name) == 1)
			exit(1);
		if (ft_is_dir(rdrs->fl_name) == 1)
			exit(1);
		if (access(rdrs->fl_name, R_OK) == -1)
			ft_redirs_bad_inf(rdrs, sh, param, errno);
		else
			ft_redirs_bad_inf(rdrs, sh, param, errno);
	}
}

void	ft_open_close(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg)
{
	if (!flg)
	{
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		ft_norm_piperf(sh, rdrs, param);
	}
	else if (flg == 1)
	{
		sh->in_fd = open(rdrs->fl_name, O_RDONLY);
		ft_norm_pipers(sh, rdrs, param);
	}
	else if (flg == 2)
	{
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		ft_norm_pipert(sh, rdrs, param);
	}
	else if (flg == 3)
	{
		sh->in_fd = open(rdrs->fl_name, O_RDONLY);
		ft_norm_pipers(sh, rdrs, param);
		unlink(rdrs->fl_name);
	}
}

void	ft_piper(t_sh *sh, t_parms *param, int leng, pid_t pid)
{
	t_sh	*head;
	int		status;

	head = sh;
	param->ppc_idx = 0;
	tcgetattr(STDOUT_FILENO, &param->state);
	while (head)
	{
		if (!ft_strcmp(head->type, "CMD"))
		{
			if (param->ppc_idx == 0)
				ft_fst_pp_forker(sh, param, head);
			else if (param->ppc_idx != 0 && param->ppc_idx != leng)
				ft_mid_pp_forker(sh, param, head);
			else if (param->ppc_idx == leng)
				pid = ft_lst_pp_forker(sh, param, head);
			param->ppc_idx++;
		}
		head = head->next;
	}
	ft_close_ppchain(param, sh);
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	ft_updt_stts(status, param, param->state);
}
