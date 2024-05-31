/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:51:20 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 10:35:08 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_norm_fexit(char **cmd)
{
	write(2, cmd[1], ft_len(cmd[1]));
	write(2, " : numeric argument required\n", 29);
	exit(255);
}

void	ft_norm_sexit(t_parms *param, char **cmd)
{
	write(2, "exit: ", 7);
	write(2, cmd[1], ft_len(cmd[1]));
	write(2, " : numeric argument required\n", 29);
	param->ext_stts = 255;
	exit (param->ext_stts);
}

void	ft_norm_texit(char **cmd)
{
	write(2, "exit: ", 7);
	write(2, cmd[1], ft_len(cmd[1]));
	write(2, " : numeric argument required\n", 29);
	exit (255);
}

void	ft_norm_fiexit(long long ex_sts, char **cmd, t_parms *param)
{
	if (!ft_only_digits(cmd[1]))
		ft_norm_sexit(param, cmd);
	else
	{
		ex_sts = ft_ext_atoi(cmd[1], 0, 0, 0);
		if (ex_sts >= 0)
		{
			if (ex_sts >= 0 && ex_sts <= 255)
				exit (ex_sts);
			else if (ex_sts >= 256 && ex_sts <= 999999999999999999)
				exit (ex_sts % 256);
			else if (ex_sts > 9223372036854775807)
				ft_norm_texit(cmd);
			exit (255);
		}
		else
		{
			if (ex_sts <= -1 && ex_sts >= -999999999999999999)
				exit (256 + (ex_sts % 256));
		}
	}
}

int	ft_exit(char **cmd, t_parms *param)
{
	long long	ex_sts;

	if (!cmd || !(*cmd))
		return (0);
	ex_sts = 0;
	printf("exit\n");
	if (ft_tlen(cmd) == 1)
		exit (param->ext_stts);
	else if (ft_tlen(cmd) > 2 && ft_only_digits(cmd[1]))
	{
		write(2, "exit: too many arguments\n", 26);
		param->ext_stts = 1;
		return (param->ext_stts);
	}
	else if (ft_tlen(cmd) > 2 && !ft_only_digits(cmd[1]))
		ft_norm_fexit(cmd);
	else if (ft_tlen(cmd) == 2)
		ft_norm_fiexit(ex_sts, cmd, param);
	return (param->ext_stts);
}
