/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:05:37 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/28 18:56:59 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <signal.h>
#include <stdio.h>


// int	g_signal = 0;
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
			param->ext_stts = 1;
			write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
			write(2, ": ambiguous redirect\n", 22);
			exit (param->ext_stts);
		}
		rdrs = rdrs->next;
	}
	ft_sngl_cmd_rdr_strms(sh);
}
// void 	ft_handler2(int sig)//!signal
// {
// 	if (sig == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		g_signal = 1;
// 		//exit(1);
// 		//rl_replace_line("", 0);
// 		//rl_on_new_line();
// 		// rl_redisplay();
// 	}
// 	else if (sig == SIGQUIT){
// 		printf("Quit: 3\n");
// 	}
// }

static void ft_handler_redirect(int sig)
{
	if (g_inchild)
	{
		printf("\n");
		g_inchild = 0;
		return ;
	}
	ft_handler(sig);
}

int	ft_other_cmd(t_sh *sh, t_parms *param)
{
	char	*bin_file;
	pid_t	pid;
	int		ex_sts;

	signal(SIGINT, ft_handler_redirect);
	g_inchild = 1;
	pid = fork();
	ex_sts = 0;
	if (pid == -1)
		perror("lminishell ");
	if (pid == 0)
	{
		// signal(SIGINT, ft_handler2);//!signal
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
		write(2, "lminishell ", 12);
		write(2, sh->value[0], ft_len(sh->value[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	// signal(SIGINT, ft_handler);//!signal
	wait(&ex_sts);
	g_inchild = 0;
	if (WIFEXITED(ex_sts))
		param->ext_stts = WEXITSTATUS(ex_sts);
	return (param->ext_stts);
}
