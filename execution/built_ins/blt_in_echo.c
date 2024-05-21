/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:13:55 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/16 18:22:48 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	if (!s)
		write(1, "(null)", 7);
	while (s[++i])
		write(1, &s[i], 1);
}

static int	ft_all_dashes(char *cmd)
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

static int	ft_dasher(char **cmd)
{
	int	i;

	if (!cmd || !(*cmd))
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (ft_all_dashes(cmd[i]) == 1)
			return (i);
	}
	return (-1);
}

static int	ft_args_are_flags(char **cmd)
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

static int	ft_imposter_flag(char **cmd)
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

static int	ft_n_ln_chckr(char *cmd)
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

static int	ft_n_gang(char **cmd)
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

static int	ft_glued_flags(char **cmd)
{
	if (!cmd || !(*cmd))
		return (0);
	if (ft_tlen(cmd) == 1)
		return(-4);
	else if (ft_n_gang(cmd) == -2)
		return (-3);
	else
		return (ft_n_gang(cmd));
}

void	ft_norm_echo(t_sh *sh, int n_line, int i, t_parms *param)
{
	int	sz;

	if (!sh)
		return ;
	sz = ft_tlen(sh->value);
	if (sz > 1 && ft_n_ln_chckr(sh->value[1]) == 1)
		n_line = 1;
	param->ext_stts = 0;
	while (i < sz)
	{
		ft_putstr(sh->value[i]);
		if (i < sz - 1)
			ft_putstr(" ");
		i++;
	}
	
	if (!n_line)
		ft_putstr("\n");
}

static int	ft_norm_echot()
{
	ft_putstr("\n");
	return (0);
}

void ft_one_dash(t_sh *sh)
{
	int i;
	int suppress_newline;
	int	sz;

	if (!sh)
		return ;
	i = 0;
	suppress_newline = 0;
	if (!sh->value)
		return ;
	sz = ft_tlen(sh->value);
	while (++i < sz)
	{
		ft_putstr(sh->value[i]);
		if (i < sz - 1)
			ft_putstr("\n");
	}
	if (!suppress_newline)
		ft_putstr("\n");
	return ;
}

int	ft_echo(t_sh *sh, t_parms *param)
{
	int	i;
	int	n_line;

	if (!sh || !param)
		return (0);
	i = 0;
	n_line = 0;
	if (!sh->value)
		return (1);
	if (ft_dasher(sh->value) != -1)
	{
		n_line = 0;
		ft_norm_echo(sh, n_line, ft_dasher(sh->value), param);
		return (param->ext_stts);
	}
	if (!ft_args_are_flags(sh->value))
	{
		i = ft_imposter_flag(sh->value);
		if (!ft_n_ln_chckr(sh->value[1]) && sh->value[1][0] == '-')
			i--;
	}
	else
	{
		if (ft_glued_flags(sh->value) == -3)
			return (param->ext_stts);
		i = ft_glued_flags(sh->value);
		if (ft_glued_flags(sh->value) == -4)
			return (ft_norm_echot());
	}
	ft_norm_echo(sh, n_line, i, param);
	return (param->ext_stts);
}
