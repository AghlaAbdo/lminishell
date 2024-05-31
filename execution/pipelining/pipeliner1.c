/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:14:08 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:37:28 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_close_ppchain(t_parms *param, t_sh *sh)
{
	int	(*pp_chain)[2];
	int	i;
	int	sz;

	i = 1;
	sz = ft_pp_chain_len(sh);
	pp_chain = param->pp_chain;
	if (sz == 1)
		ft_norm_dclose(pp_chain[0][0], pp_chain[0][1]);
	else
	{
		while (i < sz)
			ft_norm_sclose(pp_chain, i++);
	}
	return ;
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

void	ft_redirs_bad_inf(t_rdr *rdrs, t_sh *sh, t_parms *param, int err)
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

void	ft_resolve_redirs(t_parms *param, t_sh *sh, t_rdr	*rdrs)
{
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
			else if (!ft_strcmp(rdrs->mode, "<<"))
				ft_open_close(sh, rdrs, param, 3);
		}
		else
			ft_norm_unlink(param, rdrs);
		rdrs = rdrs->next;
	}
	ft_redir_strms(sh);
}

void	ft_fst_pp_exec(t_parms *param, t_sh *curr_sh)
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
	ft_norm_dclose(curr_sh->in_fd, curr_sh->out_fd);
	if (ft_is_builtin(curr_sh->value[0]))
		exit(ft_router(curr_sh, param, 0));
	if (execve(bin_file, curr_sh->value, ft_env_to_dp(&param->env)) == -1)
		perror("lminishell :");
}
