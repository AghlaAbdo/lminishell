/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:22:20 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/02 16:27:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_sngl_cmd_rdr_strms(t_sh *sh)
{
	if (sh->in_fd != -1)
	{
		if (dup2(sh->in_fd, STDIN_FILENO) == -1)
			ft_perror("signle cmd file's read");
	}
	if (sh->out_fd != -1)
	{
		if (dup2(sh->out_fd, STDOUT_FILENO) == -1)
			ft_perror("fsignle cmd file's write");
	}
	ft_norm_dclose(sh->in_fd, sh->out_fd);
}

static void	ft_handle_redirs(t_sh *sh, t_parms *param)
{
	t_rdr	*rdrs;
	(void)param;

	if (sh->rdr == NULL)
		return ;
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
			exit (param->ext_stts);
		}
		rdrs = rdrs->next;
	}
	ft_sngl_cmd_rdr_strms(sh);
}

void	ft_norm_other_cmd(t_sh *sh, t_parms *param, int err)
{
	if (err == 14)
	{
		write(2, sh->value[0], ft_len(sh->value[0]));
		write(2, ": command not found\n", 21);
		param->ext_stts = 127;
	}
	else if (err == EACCES)
	{
		write(2, sh->value[0], ft_len(sh->value[0]));
		write(2, ": permission denied\n", 21);
		param->ext_stts = 126;
	}
	else
	{
		perror("execve");
		param->ext_stts = 1;
	}
}

int	ft_other_cmd(t_sh *sh, t_parms *param)
{
	char *bin_file;
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("single command execution !");
	bin_file = ft_path_parser(param->envp, sh->value[0], param);
	if (pid == 0)
	{
		if (sh->rdr != NULL)
			ft_handle_redirs(sh, param);
		if (execve(bin_file, sh->value, param->envp) == -1)
			ft_norm_other_cmd(sh, param, errno);
	}
	wait(&param->ext_stts);
	if (param->ext_stts == 256)
		return (1);
	return (param->ext_stts);
}
