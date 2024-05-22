/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:17:23 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/21 19:45:29 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <stdio.h>

static void	ft_fst_pp_executer(t_sh *sh, t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;
	(void)sh;
	fprintf(stderr, "---------------------FIRST CMD : %s ---------------------\n", curr_sh->value[0]);
	bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	if (!bin_file && ft_is_builtin(curr_sh->value[0]) != 1)
		ft_norm_nfound_cmd(curr_sh);
	if (curr_sh->in_fd != -1)
	{
		if (dup2(curr_sh->in_fd, STDIN_FILENO) == -1)
			ft_perror("pipe's write");
	}
	ft_norm_dup2_out(curr_sh, param);
	ft_norm_close(param->pp_chain, param->ppc_idx);
	ft_norm_dclose(curr_sh->in_fd,curr_sh->out_fd);
	if (ft_is_builtin(curr_sh->value[0]))
		exit(ft_router(curr_sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		ft_perror("execve");
}

static void	ft_lst_pp_executer(t_sh *sh, t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;
	(void)sh;
	fprintf(stderr, "---------------------LAST CMD : %s ---------------------\n", curr_sh->value[0]);
	bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	if (!bin_file)
		ft_norm_child_stts(curr_sh, param, 127);
	ft_norm_dup2_in(curr_sh, param);
	if (curr_sh->out_fd != -1)
	{
		if (dup2(curr_sh->out_fd, STDOUT_FILENO) == -1)
			ft_perror("pipe's read");
	}
	ft_norm_close(param->pp_chain, param->ppc_idx - 1);
	ft_norm_dclose(curr_sh->in_fd,curr_sh->out_fd);
	if (ft_is_builtin(curr_sh->value[0]))
			exit(ft_router(curr_sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		ft_perror("execve");
}

static void	ft_mid_pp_executer(t_sh *sh, t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;
	(void)sh;
	fprintf(stderr, "---------------------MIDDLE CMD : %s ---------------------\n", curr_sh->value[0]);
	bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	if (!bin_file)
		ft_norm_nfound_cmd(curr_sh);
	ft_norm_dup2_in(curr_sh, param);
	ft_norm_dup2_out(curr_sh, param);
	ft_norm_sclose(param->pp_chain, param->ppc_idx);
	if (ft_is_builtin(curr_sh->value[0]))
		exit(ft_router(curr_sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		ft_perror("execve");
}

static void	ft_redir_strms(t_sh *sh)
{
	if (sh->in_fd != -1)
	{
		if (dup2(sh->in_fd, STDIN_FILENO) == -1)
			ft_perror("file's read");
	}
	if (sh->out_fd != -1)
	{
		if (dup2(sh->out_fd, STDOUT_FILENO) == -1)
			ft_perror("file's write");
	}
}

void	ft_close_ppchain(t_parms *param, t_sh *sh)
{
	int		(*pp_chain)[2];
	int	i;
	int	sz;

	i = -1;
	sz = ft_pp_chain_len(sh);
	pp_chain = param->pp_chain;
	while (++i < sz)
		ft_norm_sclose(pp_chain, i);
	return;
}

void	ft_redirs_bad_inf(t_rdr * rdrs, t_sh *sh, t_parms *param, int err)
{
	if (err == 2)
	{
		write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
		write(2, ": No such file or directory\n", 29);
		ft_close_ppchain(param, sh);
		close(sh->out_fd);
		param->ext_stts = 1;
		exit(param->ext_stts);
	}
}

void	ft_open_close(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg)
{
	if (!flg)
	{
		if (sh->out_fd != -1)
			close(sh->out_fd);
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (flg == 1)
	{
		if (sh->in_fd != -1)
			close(sh->in_fd);
		sh->in_fd = open(rdrs->fl_name, O_RDONLY);
		if (sh->in_fd == -1)
			ft_redirs_bad_inf(rdrs, sh, param, errno);
	}
	else if (flg == 2)
	{
		if (sh->out_fd != -1)
				close(sh->in_fd);
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}

void	ft_resolve_redirs(t_parms *param, t_sh *sh)
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
	ft_redir_strms(sh);
}

static void	ft_pp_forker(t_sh *sh, t_parms *param, t_sh *curr_sh, int leng)
{
	pid_t	pid;
	(void)sh;
	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (pid == 0)
	{
		ft_fds_collector(param, leng, -1);
		ft_resolve_redirs(param, curr_sh);
		if (param->ppc_idx == 0)
			ft_fst_pp_executer(sh, param, curr_sh);
		else if (param->ppc_idx != 0 && param->ppc_idx != leng)
			ft_mid_pp_executer(sh, param, curr_sh);
		else if (param->ppc_idx == leng)
			ft_lst_pp_executer(sh, param, curr_sh);
	}
}

void	ft_piper(t_sh *sh, t_parms *param)
{
	t_sh	*head;
	int		i;

	pipe(param->child_stts);
	i = -1;
	param->ppc_idx = 0;
	head =  sh;
	param->pp_chain = ft_pp_chain_creator(sh);
	// prnt_rdr(head->rdr);
	// prnt_sh(head);
	while (head)
	{
		if (ft_strcmp(head->type, "CMD") == 0)
		{
			ft_pp_forker(sh, param, head, ft_pp_chain_len(sh));
			param->ppc_idx++;
		}
		head = head->next;
	}
	while (++i < ft_pp_chain_len(sh))
		ft_norm_close(param->pp_chain, i);
	while (waitpid(-1, &param->ext_stts, 0) != -1)
		;
	ft_norm_ext_stts(param);
}
