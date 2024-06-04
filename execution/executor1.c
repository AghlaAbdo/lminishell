/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:31:07 by srachidi          #+#    #+#             */
/*   Updated: 2024/06/01 12:07:25 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_blt_rdrs_bad_inf(t_rdr * rdrs, t_sh *sh, t_parms *param, int err)
{
	if (err == 2)
	{
		write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
		write(2, ": No such file or directory\n", 29);
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

int	ft_router(t_sh *sh, t_parms *param, int ex_stts)
{
	t_sh	*head;

	head = sh;
	if (head->value)
	{
		if (ft_strcmp(head->value[0], "env") == 0)
			ex_stts = ft_env(sh, param);
		else if (ft_strcmp(head->value[0], "pwd") == 0)
			ex_stts = ft_pwd(sh, param);
		else if (ft_strcmp(head->value[0], "echo") == 0)
			ex_stts = ft_echo(sh, param, 0, 0);
		else if (ft_strcmp(head->value[0], "cd") == 0)
			ex_stts = ft_cd(sh, param);
		else if (ft_strcmp(head->value[0], "exit") == 0)
			ex_stts = ft_exit(sh->value, param);
		else if (ft_strcmp(head->value[0], "export") == 0)
			ex_stts = ft_export(sh, param, 0, 0);
		else if (ft_strcmp(head->value[0], "unset") == 0)
			ex_stts = ft_unset(sh, param);
		else
			ex_stts = ft_other_cmd(sh, param);
	}
	param->ext_stts = ex_stts;
	return (ex_stts);
}

void	ft_rstr_dflt_strm( int	sv_in, int	sv_out)
{
	if (dup2(sv_out, STDOUT_FILENO) == -1)
		perror("dup2");
	if (dup2(sv_in, STDIN_FILENO) == -1)
		perror("dup2");
	ft_norm_dclose(sv_in, sv_out);
}

int	ft_handle_built_redirsf(t_rdr *rdrs, t_sh *sh, t_parms *param)
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
		if (!rdrs->flag && ft_handle_built_redirsf(rdrs, sh, param) == -2)
			return (-2);
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
