/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_echo1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:24:17 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/30 19:08:28 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	if (!s)
		write(1, "(null)", 7);
	while (s[++i])
		write(1, &s[i], 1);
}

int	ft_all_dashes(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != '-')
			return (0);
	}
	return (1);
}

int	ft_dasher(char **cmd)
{
	int	i;

	if (!cmd || !(*cmd))
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (ft_len(cmd[i]) == 0)
			return (-1);
		if (ft_all_dashes(cmd[i]) == 1)
			return (i);
	}
	return (-1);
}

int	ft_args_are_flags(char **cmd)
{
	int	i;

	if (!cmd || !(*cmd))
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (0);
	}
	return (1);
}

int	ft_imposter_flag(char **cmd)
{
	int	i;

	if (!cmd || !(*cmd))
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (i);
	}
	return (-1);
}
