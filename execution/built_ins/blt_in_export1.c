/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_export1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:21:03 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 13:25:02 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_isthere_equal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-1);
}

void	ft_no_equal_found(char *s, t_parms *param)
{
	if (ft_valid_identifier(s))
	{
		if (!ft_env_exists(&param->exprt_env, s))
			ft_env_insrt(&param->exprt_env, s, NULL);
	}
	else
		ft_exprt_error(param, s);
}

void	ft_key_value_export(char *s, t_parms *param, int eq_indx)
{
	if (!ft_env_exists(&param->exprt_env, ft_substr(s, 0, eq_indx)))
	{
		ft_env_insrt(&param->exprt_env, ft_substr(s, 0, eq_indx),
			ft_substr(s, eq_indx + 1, ft_len(s)));
		ft_env_insrt(&param->env, ft_substr(s, 0, eq_indx),
			ft_substr(s, eq_indx + 1, ft_len(s)));
	}
	else
	{
		ft_env_updt(&param->exprt_env, ft_substr(s, 0, eq_indx),
			ft_substr(s, eq_indx + 1, ft_len(s)));
		ft_env_updt(&param->env, ft_substr(s, 0, eq_indx),
			ft_substr(s, eq_indx + 1, ft_len(s)));
	}
}

void	ft_norm_exprt(t_parms *param, char *s, int eq_indx)
{
	ft_env_insrt(&param->exprt_env, ft_substr(s, 0, eq_indx), "");
	ft_env_insrt(&param->env, ft_substr(s, 0, eq_indx), "");
}
