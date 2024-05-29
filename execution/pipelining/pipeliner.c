/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:28:47 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 09:03:57 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

//!-------------------------------------------------\fds collectors\--------------------------------------------------
void	ft_close_ppchain(t_parms *param, t_sh *sh)
{
	int		(*pp_chain)[2];
	int	i;
	int	sz;

	i = -1;
	sz = ft_pp_chain_len(sh);
	pp_chain = param->pp_chain;
	if (sz == 1)
		ft_norm_dclose(pp_chain[0][0], pp_chain[0][1]);
	else
	{
		while (++i < sz)
			ft_norm_sclose(pp_chain, i);
	}
	return;
}

//!-------------------------------------------------\redirectors\--------------------------------------------------
void	ft_open_close(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg)
{
	if (!flg)
	{
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (sh->out_fd == -1)
		{
			if (ft_is_dir(rdrs->fl_name) == 1)
				exit(1);
			if (access(rdrs->fl_name, W_OK) == -1)
				ft_redirs_bad_inf(rdrs, sh, param, errno);
			else
				ft_redirs_bad_inf(rdrs, sh, param, errno);
		}
	}
	else if (flg == 1)
	{
		sh->in_fd = open(rdrs->fl_name, O_RDONLY);
		if (sh->in_fd == -1)
		{
			if (ft_is_dir(rdrs->fl_name) == 1)
				exit(1);
			if (access(rdrs->fl_name, R_OK) == -1)
			{
				ft_redirs_bad_inf(rdrs, sh, param, errno);
				exit(1);
			}
			else
				ft_redirs_bad_inf(rdrs, sh, param, errno);
		}
	}
	else if (flg == 2)
	{
		sh->out_fd = open(rdrs->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (sh->out_fd == -1)
		{
			if (ft_is_dir(rdrs->fl_name) == 1)
				exit(1);
			if (ft_is_dir(rdrs->fl_name) == 1)
				exit(1);
			if (access(rdrs->fl_name, R_OK) == -1)
				ft_redirs_bad_inf(rdrs, sh, param, errno);
			else
				ft_redirs_bad_inf(rdrs, sh, param, errno);
		}
	}
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
	else if (err == 13)
	{
		write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
		write(2, ": Permission denied\n", 21);
		ft_close_ppchain(param, sh);
		close(sh->out_fd);
		param->ext_stts = 1;
		exit(1);
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

//!-------------------------------------------------\executers\--------------------------------------------------
void	ft_fst_pp_exec(t_parms *param,  t_sh *curr_sh)
{
	char	*bin_file;

	if (!ft_is_there_slash(curr_sh->value[0]))
		bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	else
		bin_file = curr_sh->value[0];
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
		perror("lminishell :");
}

void	ft_mid_pp_exec(t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;

	if (!ft_is_there_slash(curr_sh->value[0]))
		bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	else
		bin_file = curr_sh->value[0];
	bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	if (!bin_file)
		ft_norm_nfound_cmd(curr_sh);
	ft_norm_dup2_in(curr_sh, param);
	ft_norm_dup2_out(curr_sh, param);
	ft_norm_sclose(param->pp_chain, param->ppc_idx);
	if (ft_is_builtin(curr_sh->value[0]))
		exit(ft_router(curr_sh, param));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		perror("lminishell :");
}

void	ft_lst_pp_exec(t_parms *param, t_sh *curr_sh)
{
	char	*bin_file;

	if (!ft_is_there_slash(curr_sh->value[0]))
		bin_file = ft_path_parser(param->envp, curr_sh->value[0], param);
	else
		bin_file = curr_sh->value[0];
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
		perror("lminishell :");
}

//!-------------------------------------------------\forkers\--------------------------------------------------
void	ft_fst_pp_forker(t_sh *sh, t_parms *param, t_sh *head)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == -1)
		perror("fork first cmd");
	if (pid == 0)
	{
		while (++i < ft_pp_chain_len(sh))
			ft_norm_close(param->pp_chain, i);
		ft_resolve_redirs(param, head);
		ft_fst_pp_exec(param, head);
	}
}
void	ft_mid_pp_forker(t_sh *sh, t_parms *param, t_sh *head)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = fork();
	if (pid == -1)
		perror("fork midd cmd");
	if (pid == 0)
	{
		while (++i < ft_pp_chain_len(sh))
		{
			if (i != param->ppc_idx && i != param->ppc_idx - 1)
				ft_norm_close(param->pp_chain, i);
		}
		ft_resolve_redirs(param, head);
		ft_mid_pp_exec(param, head);
	}
}
pid_t	ft_lst_pp_forker(t_sh *sh, t_parms *param, t_sh *head)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = fork();
	if (pid == -1)
		perror("fork last cmd");
	if (pid == 0)
	{
		while (++i < ft_pp_chain_len(sh))
		{
			if (i < ft_pp_chain_len(sh) - 1)
				ft_norm_close(param->pp_chain, i);
		}
		ft_resolve_redirs(param, head);
		ft_lst_pp_exec(param, head);
	}
	return (pid);
}

//!-------------------------------------------------\pipers\--------------------------------------------------
void	ft_piper(t_sh *sh, t_parms *param)
{
	t_sh	*head;
	int		leng;
	int		status;
	struct termios	state;

	head = sh;
	leng = ft_pp_chain_len(sh);
	param->ppc_idx = 0;
	param->pp_chain = ft_pp_chain_creator(sh);
	pid_t pid = -1;
	tcgetattr(STDOUT_FILENO, &state);
	while (head)
	{
		if (!ft_strcmp(head->type, "CMD"))
		{
			if (param->ppc_idx == 0)
				ft_fst_pp_forker(sh, param, head);
			else if (param->ppc_idx != 0 && param->ppc_idx != leng)
				ft_mid_pp_forker(sh, param, head);
			else if (param->ppc_idx == leng)
				pid = ft_lst_pp_forker(sh, param, head);
			param->ppc_idx++;
		}
		head = head->next;
	}
	ft_close_ppchain(param, sh);
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	ft_updt_stts(status, param, state);
	// if (WIFEXITED(status))
	// 	param->ext_stts = WEXITSTATUS(status);
}

