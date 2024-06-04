/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:27:46 by srachidi          #+#    #+#             */
/*   Updated: 2024/06/01 11:57:07 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_blt_opn_clsf(t_sh *sh, t_rdr *rdrs, t_parms *param)
{
	sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (sh->out_fd == -1)
	{
		if (ft_is_dir(rdrs->fl_name) == 1)
		{
			param->ext_stts = 1;
			return (-2);
		}
		if (access(rdrs->fl_name, F_OK) != 0)
			return (ft_blt_rdrs_bad_inf(rdrs, sh, param, errno));
		if (access(rdrs->fl_name, W_OK) == -1)
			return (ft_blt_rdrs_bad_inf(rdrs, sh, param, 3));
	}
	return (0);
}

int	ft_blt_opn_clss(t_sh *sh, t_rdr *rdrs, t_parms *param)
{
	sh->in_fd = open(rdrs->fl_name, O_RDONLY);
	if (sh->in_fd == -1)
	{
		if (ft_is_dir(rdrs->fl_name) == 1)
		{
			param->ext_stts = 1;
			return (-2);
		}
		if (access(rdrs->fl_name, F_OK) != 0)
			return (ft_blt_rdrs_bad_inf(rdrs, sh, param, errno));
		if (access(rdrs->fl_name, R_OK) == -1)
			return (ft_blt_rdrs_bad_inf(rdrs, sh, param, 3));
	}
	return (0);
}

int	ft_blt_opn_cls(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg)
{
	if (!flg && ft_blt_opn_clsf(sh, rdrs, param) != 0)
		return (-2);
	else if (flg == 1 && ft_blt_opn_clss(sh, rdrs, param) != 0)
		return (-2);
	else if (flg == 2)
	{
		if (sh->out_fd != -1)
				close(sh->in_fd);
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (sh->out_fd == -1)
		{
			if (ft_is_dir(rdrs->fl_name) == 1)
			{
				param->ext_stts = 1;
				return (-2);
			}
			if (access(rdrs->fl_name, F_OK) != 0)
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, errno));
			if (access(rdrs->fl_name, R_OK) == -1)
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, 3));
		}
	}
	return (0);
}
