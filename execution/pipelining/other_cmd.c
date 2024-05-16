/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:22:20 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/02 16:27:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_other_cmd(t_sh *sh, t_parms *param)
{
	char *bin_file;
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("single command execution !");
	bin_file = ft_path_parser(param->envp, sh->value[0]);
	if (pid == 0)
	{
		if (execve(bin_file, sh->value, param->envp) == -1)
		{
			if (errno == 14)
			{
				write(2, sh->value[0], ft_len(sh->value[0]));
				write(2, ": command not found\n", 21);
				param->ext_stts = 127;
			}
			else if (errno == EACCES)
			{
				write(2, sh->value[0], ft_len(sh->value[0]));
				write(2, ": permission denied\n", 21);
				param->ext_stts = 126;
			}
			else
			{
				perror("execve");
				param->ext_stts = 1;
			}
		}
	}
	wait(&param->ext_stts);
	return (param->ext_stts);
}
