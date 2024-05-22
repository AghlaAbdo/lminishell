/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:53:35 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/21 19:45:22 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>

static int	ft_handle_built_redirs(t_sh *sh, t_parms *param)
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
				ft_open_close(sh, rdrs, param, 0);
			else if (!ft_strcmp(rdrs->mode, "<"))
				ft_open_close(sh, rdrs, param, 1);
			else if (!ft_strcmp(rdrs->mode, ">>"))
				ft_open_close(sh, rdrs, param, 2);
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
			ft_exit(sh->value, param);
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
		perror("out dup");
	if (ft_sh_sz(&sh) == 1)
	{
		if (ft_is_builtin(sh->value[0]) == 1 && sh->rdr != NULL)
			ambgs_rdr = ft_handle_built_redirs(sh, param);
		if (ambgs_rdr <= 0 )
			ft_router(sh, param);
		ft_rstr_dflt_strm(sv_in, sv_out);
	}
	else

		ft_piper(sh, param);
}
