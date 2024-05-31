/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:29:07 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 15:19:19 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_norm_dup2_in(t_sh *curr_sh, t_parms *param)
{
	if (curr_sh->in_fd == -1)
	{
		if (dup2(param->pp_chain[param->ppc_idx - 1][0], STDIN_FILENO) == -1)
			ft_perror("pipe's read");
	}
	else
	{
		if (dup2(curr_sh->in_fd, STDIN_FILENO) == -1)
			ft_perror("file's read");
	}
}

void	ft_norm_dup2_out(t_sh *curr_sh, t_parms *param)
{
	if (curr_sh->out_fd == -1)
	{
		if (dup2(param->pp_chain[param->ppc_idx][1], STDOUT_FILENO) == -1)
			ft_perror("pipe's write");
	}
	else
	{
		if (dup2(curr_sh->out_fd, STDOUT_FILENO) == -1)
			ft_perror("file's write");
	}
}

int	ft_is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (-1);
	if (S_ISDIR(statbuf.st_mode))
	{
		write(2, path, ft_len(path));
		write(2, ": is a directory\n", 28);
		return (1);
	}
	else
		return (0);
}

int	ft_norm_err_msgg(t_sh *sh, t_parms *param)
{
	write(2, "lminishell ", 12);
	write(2, sh->value[0], ft_len(sh->value[0]));
	write(2, ": command not found\n", 21);
	param->ext_stts = 127;
	return (param->ext_stts);
}

int	ft_strncmpx(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
