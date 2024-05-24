/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:06:27 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/24 21:05:49 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*splt_var(t_parms *prm, char *var, char *bef, char *aft)
{
	char	**arr;
	t_var	*var_t;
	int		i;

	var_t = (t_var *)prm->var;
	arr = my_split(var, ' ');
	i = 0;
	var_t->wrd = ft_pstrjoin(bef, arr[i]);
	var_t->type = 'N';
	prm->v_len = 0;
	while (arr[++i +1])
	{
		prm->v_len++;
		ft_var_insrt(&var_t, ft_var_new(arr[i], 'N', 0));
		var_t = var_t->next;
	}
	prm->l_len = ft_len(arr[i]);
	aft = ft_pstrjoin(arr[i], aft);
	ft_var_insrt(&var_t, ft_var_new(aft, 'L', 0));
	return (NULL);
}

// char	*check_vars(t_parms *prm, char *wd, int i, int j)
// {
// 	t_token	*tkn;
// 	char	*value;
// 	char	*var;

// 	i = 0;
// 	while (wd[i])
// 	{
// 		if (wd[i] == '$')
// 	}
// }

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
	if (var_t->type!= 'D' && (ft_strchr(value, ' ') || ft_strchr(value, 9)))
	{
		prm->len = ft_len(var);
		tkn->type = 'N';
		return (var);
	}
	else if (value)
	{
		prm->len = ft_len(value);
		return (ft_pstrjoin(value, wd + j));
	}
	else
		return (wd + j);
}

char	*expand_it(char *wd, t_parms *prm, int i)
{
	t_token	*tkn;
	char	*var;
	char	*res;
	int		j;

	tkn = (t_token *)prm->tkn;
	j = i + 1;
	var = ft_trim(wd, i + 1);
	res = check_vlid_var(prm, wd, i, &j);
	if (res)
		return (res);
	var = ft_env_srch(var, &prm->env);
	if (tkn->prev && (tkn->prev->type == '>' || tkn->prev->type == '<'))
		return (check_n_file(prm, wd, i, j));
	if (var && (prm->c == 'V' || prm->c == 'N' || prm->c == 'L')
		&& (ft_strchr(var, ' ') || ft_strchr(var, '\t'))
		&& !check_splt(prm->tkn))
		return (splt_var(prm, var, get_prev(wd, i), wd + j));
	if (var)
	{
		prm->len = ft_len(var);
		return (ft_pstrjoin(var, wd + j));
	}
	return (wd + j);
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
			res = expand_it(token, prm, i);
			if (!res)
				return (NULL);
			token = ft_pstrjoin(get_prev(token, i), res);
			while (prm->len-- > 1)
			{
				// printf("\tskipped: [%c]\n", token[i]);
				i++;
			}
		}
		if (token[i] && token[i] != '$')
			i++;
	}
	return (token);
}

void	join_vars(t_token **tkn, t_var **var, t_parms *prm, int *flag)
{
	char	*res;
	t_token	*rmv;

	res = "";
	rmv = (t_token *)prm->tkn;
	printf("\tt\tto rmv: [%s]\n", rmv->token);
	while ((*var) && (*var)->type != 'N')
	{
		res = ft_pstrjoin(res, (*var)->wrd);
		*var = (*var)->next;
	}
	if (*var && (*var)->type == 'N')
	{
		res = ft_pstrjoin(res, (*var)->wrd);
		*var = (*var)->next;
	}
		printf("res to add: [%s]\t*flag: %d\n", res, *flag);
	// if (*flag)
	// {
	// 	if (res && *res)
	// 	{
	// 		ft_token_insrt(tkn, ft_token_new(res, 'V', 0));
	// 		*tkn = (*tkn)->next;
	// 		prm->t_len++;
	// 	}
	// 	else
	// 		ft_token_rmv(tkn, rmv);
	// 	*flag = 1;
	// }
	// else
	// {
		if (res && *res)
		{
			(*tkn)->token = res;
			prm->t_len++;
		}
		else
		{
		printf("what about here?\n");
			ft_token_rmv(tkn, rmv);
		}
			*flag = 1;
	// }
}
