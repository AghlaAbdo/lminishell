/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:53:35 by srachidi          #+#    #+#             */
/*   Updated: 2024/06/01 12:08:57 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	ft_exec(t_sh *sh, t_parms *param, int ambgs_rdr, int sp_fd)
{
	int	sv_in;
	int	sv_out;
	pid_t	pid;

	pid = 0;
	ambgs_rdr = -1;
	if (!sh || !param)
		return ;
	sv_in = dup(STDIN_FILENO);
	if (sv_in == -1)
		perror("in dup");
	sv_out = dup(STDOUT_FILENO);
	if (sv_out == -1)
	{
		perror("lminishell :");
		close (sv_in);
	}
	if (ft_sh_sz(&sh) == 1)
	{
		if (!sh->value)
		{
			ft_norm_dclose(sv_in, sv_out);
			if (sh->rdr != NULL)
			{
				if (!ft_strcmp(sh->rdr->mode, ">"))
				{
					if (!sh->rdr->flag)
					{
						sp_fd = open(sh->rdr->fl_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
						if (sp_fd == -1)
							perror("sp_fd");
						close(sp_fd);
					}
					else
					{
						param->ext_stts = 1;
						write(2, "lminishell :", 13);
						write(2, sh->rdr->fl_name, ft_len(sh->rdr->fl_name));
						write(2, ": ambiguous redirect\n", 22);
						return ;
					}
				}
				else if (!ft_strcmp(sh->rdr->mode, ">>"))
				{
					if (!sh->rdr->flag)
					{
						sp_fd = open(sh->rdr->fl_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
						if (sp_fd == -1)
							perror("sp_fd");
						close(sp_fd);
					}
					else
					{
						param->ext_stts = 1;
						write(2, "lminishell :", 13);
						write(2, sh->rdr->fl_name, ft_len(sh->rdr->fl_name));
						write(2, ": ambiguous redirect\n", 22);
						return ;
					}
				}
				if (!access(sh->rdr->fl_name, F_OK))
				{
					param->ext_stts = 0;
					return ;
				}
				else
				{
					write(2, "lminishell : ", 14);
					write(2, sh->rdr->fl_name, ft_len(sh->rdr->fl_name));
					write(2, ": No such file or directory\n", 29);
					param->ext_stts = 1;
					return ;
				}
			}
		}
		if (!sh->value)
			ambgs_rdr = ft_handle_built_redirs(sh, param);
		if (ft_is_builtin(sh->value[0]) == 1 && sh->rdr != NULL)
			ambgs_rdr = ft_handle_built_redirs(sh, param);
		if (ambgs_rdr == -2)
			return (ft_norm_dclose(sv_in, sv_out));
		if (ambgs_rdr == 0 || ambgs_rdr == -1)
			ft_router(sh, param, 0);
		ft_rstr_dflt_strm(sv_in, sv_out);
	}
	else
	{
		ft_norm_dclose(sv_in, sv_out);
		ft_piper(sh, param, ft_pp_chain_len(sh), pid);
	}
}
