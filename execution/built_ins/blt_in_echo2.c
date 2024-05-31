/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_echo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:23 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 12:31:37 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_n_ln_chckr(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	if (ft_strcmp(cmd, "-n") == 0)
		return (1);
	if (cmd[0] == '-')
	{
		if (ft_strcmp(cmd, "-") == 0)
			return (0);
		while (cmd[++i])
		{
			if (cmd[i] != 'n')
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

int	ft_n_gang(char **cmd)
{
	int	i;
	int	j;

	if (!cmd || !(*cmd))
		return (0);
	i = 0;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'n')
				return (i);
		}
	}
	return (-2);
}

void	ft_norm_echo_lif(t_sh *sh, int *i)
{
	*i = ft_imposter_flag(sh->value);
	if (!ft_n_ln_chckr(sh->value[1]) && sh->value[1][0] == '-')
		(*i)--;
}
