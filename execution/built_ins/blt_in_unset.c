/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:42:15 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 13:20:24 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static	int	ft_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int	ft_is_valid(char c)
{
	return (ft_is_alpha(c) || (c >= '0' && c <= '9') || c == '_');
}

int	ft_valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '_' && !ft_is_alpha(s[0]))
		return (0);
	while (s[++i])
	{
		if (!ft_is_valid(s[i]))
			return (0);
	}
	return (1);
}

void	ft_norm_unset(t_sh *sh, t_parms *param, int i)
{
	write(2, "unset: ", 8);
	write(2, sh->value[i], ft_len(sh->value[i]));
	write(2, ": not a valid identifier\n", 26);
	param->ext_stts = 1;
}

int	ft_unset(t_sh *sh, t_parms *param)
{
	int	i;

	if (!sh->value)
		return (1);
	i = 0;
	if (ft_tlen(sh->value) == 1)
	{
		param->ext_stts = 0;
		return (param->ext_stts);
	}
	else
	{
		while (sh->value[++i])
		{
			if (ft_valid_identifier(sh->value[i]))
			{
				ft_env_rmv(&param->env, sh->value[i]);
				ft_env_rmv(&param->exprt_env, sh->value[i]);
				param->ext_stts = 0;
			}
			else
				ft_norm_unset(sh, param, i);
		}
	}
	return (param->ext_stts);
}
