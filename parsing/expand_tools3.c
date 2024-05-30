/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:25:17 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/30 20:32:24 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_vlid_var(t_parms *prm, char *wd, int i, int *j)
{
	char	*var;
	char	*res;

	res = dollar_var(prm, wd + i, &i);
	if (res)
		return (res);
	var = ft_trim(wd, i +1);
	skip_var_name(wd, j);
	if (!ft_strcmp(var, "$?"))
	{
		prm->len = 2;
		return (ft_pstrjoin(ft_itoa(prm->ext_stts), wd + i + 2));
	}
	if (wd[i +1] >= '0' && wd[i +1] <= '9')
		return (get_n_var(prm, wd, var, i));
	if (wd[i +1] != '_' && !((wd[i +1] >= 'a' && wd[i +1] <= 'z')
			|| (wd[i +1] >= 'A' && wd[i +1] <= 'Z')))
	{
		prm->len = 2;
		return (wd + i);
	}
	if (!*var || *(wd + i + 1) == '"')
		return (wd + i +1);
	return (NULL);
}

char	*expand_var(t_var **var_t, t_parms *prm, char *token, char *res)
{
	int	i;

	i = 0;
	if ((*var_t)->type == 'L')
		while (prm->l_len-- > 0)
			i++;
	while (token[i])
	{
		if (token[i] == '$')
		{
			prm->len = 0;
			prm->v_bef = 0;
			prm->v_aft = 0;
			res = expand_it(token, prm, i);
			if (!res)
				return (NULL);
			token = ft_pstrjoin(get_prev(token, i), res);
			while (prm->len-- > 1)
				i++;
		}
		if (token[i] && token[i] != '$')
			i++;
	}
	return (token);
}

char	*check_n_file(t_parms *prm, char *wd, int i, int j)
{
	t_token	*tkn;
	t_var	*var_t;
	char	*value;
	char	*var;

	value = ft_env_srch(ft_trim(wd, i +1), &prm->env);
	var = my_strdup(wd + i);
	i = 0;
	while (var[i] && var[i] != ' ' && var[i] != 9)
		i++;
	var[i] = '\0';
	tkn = (t_token *)prm->tkn;
	var_t = (t_var *)prm->var;
	if (var_t->type != 'D' && (ft_strchr(value, ' ') || ft_strchr(value, 9)))
	{
		tkn->type = 'N';
		return (NULL);
	}
	else if (value)
	{
		prm->len = ft_len(value);
		return (ft_pstrjoin(value, wd + j));
	}
	else
		return (wd + j);
}

void	insrt_v_last(t_parms *prm, t_var *var, char *lst, char *aft)
{
	if (prm->v_aft && *aft)
	{
		prm->v_len++;
		prm->l_len = 0;
		ft_var_insrt(&var, ft_var_new(lst, 'N', 0));
		var = var->next;
		ft_var_insrt(&var, ft_var_new(aft, 'L', 0));
	}
	else
	{
		prm->l_len = ft_len(lst);
		aft = ft_pstrjoin(lst, aft);
		ft_var_insrt(&var, ft_var_new(aft, 'L', 0));
	}
}

char	*splt_var(t_parms *prm, char **arr, char *bef, char *aft)
{
	t_var	*var;
	int		i;

	var = (t_var *)prm->var;
	i = 0;
	var->type = 'N';
	prm->v_len = 0;
	if (prm->v_bef && *bef)
	{
		var->wrd = bef;
		ft_var_insrt(&var, ft_var_new(arr[i], 'N', 0));
		prm->v_len++;
		var = var->next;
	}
	else
		var->wrd = ft_pstrjoin(bef, arr[i]);
	while (arr[++i +1])
	{
		prm->v_len++;
		ft_var_insrt(&var, ft_var_new(arr[i], 'N', 0));
		var = var->next;
	}
	insrt_v_last(prm, var, arr[i], aft);
	prm->v_len++;
	return (NULL);
}
