/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:53:35 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/26 15:30:39 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>

static int	ft_blt_rdrs_bad_inf(t_rdr * rdrs, t_sh *sh, t_parms *param, int err)
{
	if (err == 2)
	{
		write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
		write(2, ": No such file or directory\n", 28);
		ft_close_ppchain(param, sh);
		close(sh->out_fd);
		param->ext_stts = 1;
	}
	else if (err == 3)
	{
		write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
		write(2, ": Permission denied\n", 21);
		ft_close_ppchain(param, sh);
		close(sh->out_fd);
		param->ext_stts = 1;
	}
	return (-2);
}

static int	ft_blt_opn_cls(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg)
{
	if (!flg)
	{
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (sh->out_fd == -1)
		{
			if (ft_is_dir(rdrs->fl_name) == 1)
			{
				param->ext_stts = 1;
				return (-2);
			}
			if (access(rdrs->fl_name, W_OK) == -1)
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, 3));
			else
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, errno));
		}
	}
	else if (flg == 1)
	{
		sh->in_fd = open(rdrs->fl_name, O_RDONLY);
		if (sh->in_fd == -1)
		{
			if (ft_is_dir(rdrs->fl_name) == 1)
			{
				param->ext_stts = 1;
				return (-2);
			}
			if (access(rdrs->fl_name, R_OK) == -1)
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, 3));
			else
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, errno));
		}
	}
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
			if (access(rdrs->fl_name, R_OK) == -1)
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, 3));
			else
				return (ft_blt_rdrs_bad_inf(rdrs, sh, param, errno));
		}
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
		}
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

int	ft_router(t_sh *sh, t_parms *param)
{
	t_sh	*head;
	int		ex_stts;

	head = sh;
	ex_stts = 0;
	if (head->value)
	{
		if (ft_strcmp(head->value[0], "env") == 0)
			ex_stts = ft_env(sh, param);
		else if (ft_strcmp(head->value[0], "pwd") == 0)
			ex_stts = ft_pwd(sh, param);
		else if (ft_strcmp(head->value[0], "echo") == 0)
			ex_stts = ft_echo(sh, param);
		else if (ft_strcmp(head->value[0], "cd") == 0)
			ex_stts = ft_cd(sh, param);
		else if (ft_strcmp(head->value[0], "exit") == 0)
			ex_stts = ft_exit(sh->value, param);
		else if (ft_strcmp(head->value[0], "export") == 0)
			ex_stts = ft_export(sh, param);
		else if (ft_strcmp(head->value[0], "unset") == 0)
			ex_stts = ft_unset(sh, param);
		else
			ex_stts = ft_other_cmd(sh, param);
	}
	param->ext_stts = ex_stts;
	return (ex_stts);
}

static void	ft_rstr_dflt_strm( int	sv_in, int	sv_out)
{
	if (dup2(sv_out, STDOUT_FILENO) == -1)
		perror("dup2");
	if (dup2(sv_in, STDIN_FILENO) == -1)
		perror("dup2");
	ft_norm_dclose(sv_in, sv_out);
}

void	ft_exec(t_sh *sh, t_parms *param)
{
	int	sv_in;
	int	sv_out;
	int	ambgs_rdr;

	ambgs_rdr = -1;
	if (!sh || !param)
		return ;
	sv_in = dup(STDIN_FILENO);
	if (sv_in == -1)
		perror("in dup");
	sv_out = dup(STDOUT_FILENO);
	if (sv_out == -1)
	{
		perror("lminishell :");
		close (sv_in);
	}
	if (ft_sh_sz(&sh) == 1)
	{
		if (ft_is_builtin(sh->value[0]) == 1 && sh->rdr != NULL)
			ambgs_rdr = ft_handle_built_redirs(sh, param);
		if (ambgs_rdr == -2)
			return (ft_norm_dclose(sv_in, sv_out));
		if (ambgs_rdr == 0 || ambgs_rdr == -1)
			ft_router(sh, param);
		ft_rstr_dflt_strm(sv_in, sv_out);
	}
	else
	{
		ft_norm_dclose(sv_in, sv_out);
		ft_piper(sh, param);
	}
}
