/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:53:35 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/30 16:14:56 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>

int	ft_norm_execf(t_sh *sh, t_parms *param, int sp_fd)
{
	if (!ft_strcmp(sh->rdr->mode, ">"))
	{
		if (!sh->rdr->flag)
		{
			sp_fd = open(sh->rdr->fl_name,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (sp_fd == -1)
				perror("sp_fd");
			close(sp_fd);
		}
		else
		{
			param->ext_stts = 1;
			write(2, "lminishell :", 13);
			write(2, sh->rdr->fl_name, ft_len(sh->rdr->fl_name));
			write(2, ": ambiguous redirect\n", 22);
			return (1);
		}
	}
	return (0);
}

int	ft_norm_execs(t_sh *sh, t_parms *param, int sp_fd)
{
	if (!ft_strcmp(sh->rdr->mode, ">>"))
	{
		if (!sh->rdr->flag)
		{
			sp_fd = open(sh->rdr->fl_name,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (sp_fd == -1)
				perror("sp_fd");
			close(sp_fd);
		}
		else
		{
			param->ext_stts = 1;
			write(2, "lminishell :", 13);
			write(2, sh->rdr->fl_name, ft_len(sh->rdr->fl_name));
			write(2, ": ambiguous redirect\n", 22);
			return (1);
		}
	}
	return (0);
}

int	ft_norm_exect(t_sh *sh, t_parms *param)
{
	if (!access(sh->rdr->fl_name, F_OK))
	{
		param->ext_stts = 0;
		return (1);
	}
	else
	{
		write(2, "lminishell : ", 14);
		write(2, sh->rdr->fl_name, ft_len(sh->rdr->fl_name));
		write(2, ": No such file or directory\n", 29);
		param->ext_stts = 1;
		return (1);
	}
	return (0);
}

int	ft_norm_execl(t_sh *sh, t_parms *param, int ambgs_rdr, int flag)
{
	if (ft_is_builtin(sh->value[0]) == 1 && sh->rdr != NULL)
	{
		flag = 1;
		param->sv_in = dup(STDIN_FILENO);
		if (param->sv_in == -1)
			perror("in dup");
		param->sv_out = dup(STDOUT_FILENO);
		if (param->sv_out == -1)
		{
			perror("lminishell :");
			close (param->sv_in);
		}
		ambgs_rdr = ft_handle_built_redirs(sh, param);
	}
	else
		ft_norm_dclose(param->sv_in, param->sv_out);
	if (ambgs_rdr == -2)
		return (ft_norm_dclose(param->sv_in, param->sv_out), 1);
	if (ambgs_rdr == 0 || ambgs_rdr == -1)
		ft_router(sh, param, 0);
	if (flag)
		ft_rstr_dflt_strm(param->sv_in, param->sv_out);
	return (0);
}

void	ft_exec(t_sh *sh, t_parms *param, int ambgs_rdr, int sp_fd)
{
	ambgs_rdr = -1;
	if (!sh || !param)
		return ;
	if (ft_sh_sz(&sh) == 1)
	{
		if (!sh->value)
		{
			if (sh->rdr != NULL)
			{
				if (ft_norm_execf(sh, param, sp_fd)
					|| ft_norm_execs(sh, param, sp_fd)
					|| ft_norm_exect(sh, param))
					return ;
			}
		}
		if (!sh->value)
			ambgs_rdr = ft_handle_built_redirs(sh, param);
		if (ft_norm_execl(sh, param, -1, 0))
			return ;
	}
	else
	{
		ft_norm_dclose(param->sv_in, param->sv_out);
		ft_piper(sh, param, ft_pp_chain_len(sh), -1);
	}
}
