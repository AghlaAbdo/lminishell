/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:16:14 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 14:20:27 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
		exit(ft_router(curr_sh, param, 0));
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
	ft_norm_dclose(curr_sh->in_fd, curr_sh->out_fd);
	if (ft_is_builtin(curr_sh->value[0]))
		exit(ft_router(curr_sh, param, 0));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		perror("lminishell :");
}

void	ft_fst_pp_forker(t_sh *sh, t_parms *param, t_sh *head)
{
	pid_t	pid;
	int		i;
	t_rdr	*rdrs;

	rdrs = NULL;
	i = 0;
	pid = fork();
	if (pid == -1)
		perror("fork first cmd");
	if (pid == 0)
	{
		while (++i < ft_pp_chain_len(sh))
			ft_norm_close(param->pp_chain, i);
		ft_resolve_redirs(param, head, rdrs);
		ft_fst_pp_exec(param, head);
	}
}

void	ft_mid_pp_forker(t_sh *sh, t_parms *param, t_sh *head)
{
	pid_t	pid;
	int		i;
	t_rdr	*rdrs;

	rdrs = NULL;
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
		ft_resolve_redirs(param, head, rdrs);
		ft_mid_pp_exec(param, head);
	}
}

pid_t	ft_lst_pp_forker(t_sh *sh, t_parms *param, t_sh *head)
{
	pid_t	pid;
	int		i;
	t_rdr	*rdrs;

	rdrs = NULL;
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
		ft_resolve_redirs(param, head, rdrs);
		ft_lst_pp_exec(param, head);
	}
	return (pid);
}
