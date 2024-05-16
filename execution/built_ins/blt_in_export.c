/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:59:20 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/10 09:12:17 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int ft_isthere_equal(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-1);
}

static void ft_no_equal_found(char *s, t_parms *param)
{
	if (ft_valid_identifier(s))
	{
		if (!ft_env_exists(&param->exprt_env, s))
			ft_env_insrt(&param->exprt_env, s, NULL);
		//!makidir walo fl case dyal update
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

void	ft_equal_exists(char *s, t_parms *param, int eq_indx)
{

	if (ft_valid_identifier(ft_substr(s, 0, eq_indx)))
	{
		if (eq_indx == ft_len(s) - 1
			|| ft_only_quotes(ft_substr(s, eq_indx + 1, ft_len(s))))//! ila kant (=) hiya akhir haja fl key.
		{
			if (!ft_env_exists(&param->exprt_env, ft_substr(s, 0, eq_indx)))
			{
				ft_env_insrt(&param->exprt_env, ft_substr(s, 0, eq_indx), "");
				ft_env_insrt(&param->env, ft_substr(s, 0, eq_indx), "");
			}
			else
			{
				if (!ft_env_srch(ft_substr(s, 0, eq_indx), &param->exprt_env)
					|| ft_len(ft_env_srch(ft_substr(s, 0, eq_indx), &param->exprt_env)) > 0)
				{
					ft_env_updt(&param->exprt_env, ft_substr(s, 0, eq_indx), "");
					ft_env_updt(&param->env, ft_substr(s, 0, eq_indx), "");
				}
			}
		}
		else
			ft_key_value_export(s, param, eq_indx);
	}
	else
		ft_exprt_error(param, s);
		
}

int	ft_is_append_mode(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if ((s[i] == '+' && s[i + 1] == '=') || s[i] == '=')
		{
			if (ft_valid_identifier(ft_substr(s, 0, i)))
			{
				if (s[i] == '=')
					return (-1);
				else
					return (i);
			}
			else
			 	return (-2);
		}
	}
	return (-1);
}

static void	ft_append_export(char *s, t_parms *param, int pls_indx)
{
	if (!ft_env_exists(&param->exprt_env, ft_substr(s, 0, pls_indx)))
	{
		ft_env_insrt(&param->exprt_env, ft_substr(s, 0, pls_indx),
			ft_substr(s, pls_indx + 2, ft_len(s)));
		ft_env_insrt(&param->env, ft_substr(s, 0, pls_indx),
			ft_substr(s, pls_indx + 2, ft_len(s)));
	}
	else
	{
		ft_env_updt(&param->exprt_env, ft_substr(s, 0, pls_indx),
			ft_strjoin(ft_env_srch(ft_substr(s, 0, pls_indx), &param->exprt_env),
				ft_substr(s, pls_indx + 2, ft_len(s))));
		ft_env_updt(&param->env, ft_substr(s, 0, pls_indx),
			ft_strjoin(ft_env_srch(ft_substr(s, 0, pls_indx), &param->env),ft_substr(s, pls_indx + 2, ft_len(s))));
	}
}

int ft_export(t_sh *sh, t_parms *param)//! sayfat l index dyal + o rat substiri o tchecke wach valid identifier 
{
	int	i;
	int	eq_indx;

	i = 0;
	eq_indx = 0;
	if (ft_tlen(sh->value) == 1)
		ft_env_prnt_fexprt(&param->exprt_env);
	else
	{
		while (sh->value[++i])
		{
			if (ft_isthere_equal(sh->value[i]) == -1)
				ft_no_equal_found(sh->value[i], param);
			else
			{
				eq_indx = ft_isthere_equal(sh->value[i]);
				if (ft_is_append_mode(sh->value[i]) >= 0)
					ft_append_export(sh->value[i], param, ft_is_append_mode(sh->value[i]));
				else if (ft_is_append_mode(sh->value[i]) == -2)
					ft_exprt_error(param, sh->value[i]);
				else if (ft_is_append_mode(sh->value[i]) == -1)
					ft_equal_exists(sh->value[i], param, eq_indx);
			}
		}
	}
	return (param->ext_stts);
}
