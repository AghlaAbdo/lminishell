/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:05:37 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 09:03:31 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <sys/termios.h>

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
			if (!ft_len(sh->rdr->fl_name))
			{
				write(2, "lminishell", 11);
				write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
				write(2, ": No such file or directory\n", 29);
			}
			else
			{
				write(2, "lminishell", 11);
				write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
				write(2, ": ambiguous redirect\n", 22);
			}
			param->ext_stts = 1;
			exit (param->ext_stts);
		}
		rdrs = rdrs->next;
	}
	ft_sngl_cmd_rdr_strms(sh);
}

int	ft_other_cmd(t_sh *sh, t_parms *param)
{
	char	*bin_file;
	pid_t	pid;
	int		ex_sts;
	struct termios	state;
	
	if (sh->value[0] != NULL && ft_len(sh->value[0]) == 0)
		return (ft_norm_err_msgg(sh, param));
	g_inchild = 1;
	pid = fork();
	ex_sts = 0;
	tcgetattr(STDOUT_FILENO, &state);
	if (pid == -1)
		perror("lminishell ");
	if (pid == 0)
	{
		if (ft_len(sh->value[0]) == 0)
			exit(0);
		if (!ft_is_there_slash(sh->value[0]))
			bin_file = ft_path_parser(param->envp, sh->value[0], param);
		else
		{
			if (!access(sh->value[0], F_OK))
			{
				if (access(sh->value[0], X_OK) != 0)
					exit(126);
			}
			bin_file = sh->value[0];
			if (ft_is_dir(bin_file) == 1)
				exit (126);
		}
		if (sh->rdr != NULL)
			ft_handle_redirs(sh, param);
		execve(bin_file, sh->value, ft_env_to_dp(&param->env));
		exit(ft_norm_err_msgg(sh, param));
	}
	wait(&ex_sts);
	g_inchild = 0;
	ft_updt_stts(ex_sts, param, state);
	return (param->ext_stts);
}
