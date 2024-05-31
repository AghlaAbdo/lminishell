/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:05:37 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 15:37:16 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_norm_binfile(t_sh *sh, t_parms *param)
{
	char	*bin_file;

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
	return (bin_file);
}

int	ft_other_cmd(t_sh *sh, t_parms *param)
{
	char			*bin_file;
	pid_t			pid;
	int				ex_sts;
	struct termios	state;

	if (sh->value[0] != NULL && ft_len(sh->value[0]) == 0)
		return (ft_norm_err_msgg(sh, param));
	pid = fork();
	ex_sts = 0;
	tcgetattr(STDOUT_FILENO, &state);
	if (pid == -1)
		perror("lminishell ");
	if (pid == 0)
	{
		bin_file = ft_norm_binfile(sh, param);
		if (sh->rdr != NULL)
			ft_handle_redirs(sh, param);
		if (ft_is_builtin(sh->value[0]))
			ft_router(sh, param, 0);
		execve(bin_file, sh->value, ft_env_to_dp(&param->env));
		exit(ft_norm_err_msgg(sh, param));
	}
	wait(&ex_sts);
	ft_updt_stts(ex_sts, param, state);
	return (param->ext_stts);
}
