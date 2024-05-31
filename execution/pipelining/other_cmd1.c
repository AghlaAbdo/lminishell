/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:23:18 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:31:42 by srachidi         ###   ########.fr       */
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

void	ft_norm_other(t_rdr *rdrs)
{
	write(2, "lminishell", 11);
	write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
	write(2, ": No such file or directory\n", 29);
}

void	ft_norm_otherr(t_rdr *rdrs)
{
	write(2, "lminishell", 11);
	write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
	write(2, ": ambiguous redirect\n", 22);
}

void	ft_norm_otherrr(t_rdr *rdrs, t_sh *sh, t_parms *param)
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

void	ft_handle_redirs(t_sh *sh, t_parms *param)
{
	t_rdr	*rdrs;

	if (sh->rdr == NULL)
		return ;
	rdrs = sh->rdr;
	while (rdrs)
	{
		if (!rdrs->flag)
			ft_norm_otherrr(rdrs, sh, param);
		else
		{
			if (!ft_len(sh->rdr->fl_name))
				ft_norm_other(rdrs);
			else
				ft_norm_otherr(rdrs);
			param->ext_stts = 1;
			exit (param->ext_stts);
		}
		rdrs = rdrs->next;
	}
	ft_sngl_cmd_rdr_strms(sh);
}
