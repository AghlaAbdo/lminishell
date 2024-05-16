/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:17:23 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/15 13:27:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <stdio.h>

static void	ft_fst_pp_executer(t_sh *sh, t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;

	bin_file = ft_path_parser(param->envp, curr_sh->value[0]);
	if (!bin_file)
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
		exit(ft_router(sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		ft_perror("execve");
}

static void	ft_lst_pp_executer(t_sh *sh, t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;

	bin_file = ft_path_parser(param->envp, curr_sh->value[0]);
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
		exit(ft_router(sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		ft_perror("execve");
}

static void	ft_mid_pp_executer(t_sh *sh, t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;

	bin_file = ft_path_parser(param->envp, curr_sh->value[0]);
	if (!bin_file)
		ft_norm_nfound_cmd(curr_sh);
	ft_norm_dup2_in(curr_sh, param);
	ft_norm_dup2_out(curr_sh, param);
	ft_norm_sclose(param->pp_chain, param->ppc_idx);
	if (ft_is_builtin(curr_sh->value[0]))
		exit(ft_router(sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		ft_perror("execve");
}

void	ft_resolve_redirs(t_parms *param, t_sh *sh)
{
	t_rdr	*rdr_head;
	(void)param;

	if (sh->rdr == NULL)
		return ;
	rdr_head = sh->rdr;
	while (rdr_head)
	{
		if (sh->in_fd != -1 || sh->in_fd != -1)
			ft_norm_dclose(sh->in_fd, sh->out_fd);
		if (!ft_strcmp(rdr_head->mode, "<"))
			sh->in_fd = open(rdr_head->fl_name, O_RDONLY);
		else if (!ft_strcmp(rdr_head->mode, ">"))
		{
			sh->out_fd = open(rdr_head->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (!ft_strcmp(rdr_head->mode, ">>"))
			sh->out_fd = open(rdr_head->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		rdr_head = rdr_head->next;
	}
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
	printf("sizeeeeeeeeee= |%d|\n",ft_sh_sz(&sh));
	while (head)
	{
		prnt_rdr(head->rdr);
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
