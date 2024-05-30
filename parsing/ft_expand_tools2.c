/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:06:27 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:04 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	check_space(t_parms *prm, char **var, char *wd, int i)
{
	int	j;

	j = 0;
	if (*var && ((*var)[0] == ' ' || (*var)[0] == 9))
		prm->v_bef = 1;
	if (*var && ((*var)[ft_len(*var) - 1] == ' ' || (*var)[ft_len(*var) - 1] == 9))
		prm->v_aft = 1;
	if (*var && prm->c != 'D')
	{
		while ((*var)[j] && ((*var)[j] == ' ' || (*var)[i] == 9))
			j++;
		if (!(*var)[j] && j && (i || *wd))
			return (1);
		*var = ft_strtrim(*var, " \t");
	}
	return (0);
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
	if (check_space(prm, &var, wd, i))
		return (ft_pstrjoin(" ", wd + j));
	if (tkn->prev && (tkn->prev->type == '>' || tkn->prev->type == '<'))
		return (check_n_file(prm, wd, i, j));
	if (var && (prm->c == 'V' || prm->c == 'N' || prm->c == 'L')
		&& !check_splt(prm->tkn, var))
		return (splt_var(prm, my_split(var, ' '), get_prev(wd, i), wd + j));
	if (var)
		prm->len = ft_len(var);
	if (var)
		return (ft_pstrjoin(var, wd + j));
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

// join strings and vars that have not been splited, if there is a var that have /
//		been splited it joins the first word with all the strings before, and joins /
//		the last word with the rest after it.
//	'flag' is to check wether there have been a var splited to replace the first part /
//		with the current token, then insert the rest in sep
void	join_vars(t_token **head, t_token **curr, t_var **var, t_parms *prm, int *flag)
{
	char	*res;
	t_token	*rmv;
	t_var	*var_t;

	var_t = (t_var *)prm->var;
	res = "";
	rmv = (t_token *)prm->tkn;
	// printf("\tvar: [%s][%c]\tto rmv: [%s]\n",var_t->wrd, var_t->type, rmv->token);
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
		// printf("res to add: [%s]\t*flag: %d\n", res, *flag);
	if (*flag)
	{
		if (res && *res)
		{
			ft_token_insrt(curr, ft_token_new(res, 'V'));
			*curr = (*curr)->next;
			prm->t_len++;
		}
		else if (rmv->prev && rmv->prev->type != '>' && rmv->prev->type != '<')
			ft_token_rmv(head, rmv);
		*flag = 1;
	}
	else
	{
		if ((res && *res) || var_t->type != 'V')
		{
			(*curr)->token = res;
			prm->t_len++;
		}
		else if (rmv->prev && rmv->prev->type != '>' && rmv->prev->type != '<')
			ft_token_rmv(head, rmv);
		else
			rmv->type = 'N';
		*flag = 1;
	}
}
