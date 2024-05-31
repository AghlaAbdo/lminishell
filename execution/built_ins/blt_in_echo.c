/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:13:55 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 12:38:39 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_glued_flags(char **cmd)
{
	if (!cmd || !(*cmd))
		return (0);
	if (ft_tlen(cmd) == 1)
		return (-4);
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

int	ft_norm_echot(void)
{
	ft_putstr("\n");
	return (0);
}

void	ft_one_dash(t_sh *sh)
{
	int	i;
	int	suppress_newline;
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

int	ft_echo(t_sh *sh, t_parms *param, int i, int n_line)
{
	if (!sh || !param)
		return (0);
	if (!sh->value)
		return (1);
	if (ft_dasher(sh->value) != -1)
	{
		n_line = 0;
		ft_norm_echo(sh, n_line, ft_dasher(sh->value), param);
		return (param->ext_stts);
	}
	if (!ft_args_are_flags(sh->value))
		ft_norm_echo_lif(sh, &i);
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
