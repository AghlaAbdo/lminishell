/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:27:46 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:33:54 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>

int	ft_blt_opn_cls(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg)
{
	if (!flg)
	{
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (sh->out_fd == -1)
			ft_norm_opn_cls(rdrs, param, sh, 0);
	}
	else if (flg == 1 || flg == 3)
	{
		sh->in_fd = open(rdrs->fl_name, O_RDONLY);
		if (sh->in_fd == -1)
			ft_norm_opn_cls(rdrs, param, sh, 1);
		if (flg == 3)
			unlink(rdrs->fl_name);
	}
	else if (flg == 2)
	{
		if (sh->out_fd != -1)
			close(sh->in_fd);
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (sh->out_fd == -1)
			ft_norm_opn_clss(rdrs, param, sh);
	}
	return (0);
}

int	ft_norm_hand_red(t_rdr *rdrs, t_parms *param)
{
	param->ext_stts = 1;
	write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
	write(2, ": ambiguous redirect\n", 22);
	return (param->ext_stts);
}

int	ft_norm_hand_redd(t_rdr *rdrs, t_sh *sh, t_parms *param)
{
	if (!ft_strcmp(rdrs->mode, ">"))
	{
		if (ft_blt_opn_cls(sh, rdrs, param, 0) == -2)
			return (-2);
	}
	else if (!ft_strcmp(rdrs->mode, "<"))
	{
		if (ft_blt_opn_cls(sh, rdrs, param, 1) == -2)
			return (-2);
	}
	else if (!ft_strcmp(rdrs->mode, ">>"))
	{
		if (ft_blt_opn_cls(sh, rdrs, param, 2) == -2)
			return (-2);
	}
	else if (!ft_strcmp(rdrs->mode, "<<"))
	{
		if (ft_blt_opn_cls(sh, rdrs, param, 3) == -2)
			return (-2);
	}
	return (0);
}

int	ft_handle_built_redirs(t_sh *sh, t_parms *param)
{
	t_rdr	*rdrs;

	if (sh->rdr == NULL)
		return (0);
	rdrs = sh->rdr;
	while (rdrs)
	{
		if (!rdrs->flag)
			ft_norm_hand_redd(rdrs, sh, param);
		else
		{
			param->ext_stts = 1;
			write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
			write(2, ": ambiguous redirect\n", 22);
			return (param->ext_stts);
		}
		rdrs = rdrs->next;
	}
	ft_sngl_cmd_rdr_strms(sh);
	ft_norm_dclose(sh->in_fd, sh->out_fd);
	return (0);
}
