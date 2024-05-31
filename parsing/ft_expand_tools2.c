/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:06:27 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/31 11:00:21 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_space(t_parms *prm, char **var, char *wd, int i)
{
	int	j;

	j = 0;
	if (*var && ((*var)[0] == ' ' || (*var)[0] == 9))
		prm->v_bef = 1;
	if (*var && ((*var)[ft_len(*var) - 1] == ' '
		|| (*var)[ft_len(*var) - 1] == 9))
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

static void	join_vars_normf(t_var **var, char **res)
{
	while ((*var) && (*var)->type != 'N')
	{
		*res = ft_pstrjoin(*res, (*var)->wrd);
		*var = (*var)->next;
	}
	if (*var && (*var)->type == 'N')
	{
		*res = ft_pstrjoin(*res, (*var)->wrd);
		*var = (*var)->next;
	}
}

static void	join_vars_norms(t_parms *prm, t_token **head,
	t_token **curr, char *res)
{
	t_token	*rmv;

	rmv = (t_token *)prm->tkn;
	if (res && *res)
	{
		ft_token_insrt(curr, ft_token_new(res, 'V'));
		*curr = (*curr)->next;
		prm->t_len++;
	}
	else if (rmv->prev && rmv->prev->type != '>' && rmv->prev->type != '<')
		ft_token_rmv(head, rmv);
	prm->flag = 1;
}

// join strings and vars that have not been splited, if there is a var /
// hat have been splited it joins the first word with all the strings /
//      before, and joins the last word with the rest after it.
//	'flag' is to check wether there have been a var splited to /
//		 the first part with the current token, then insert the rest in sep
void	join_vars(t_token **head, t_token **curr, t_var **var, t_parms *prm)
{
	char	*res;
	t_token	*rmv;
	t_var	*var_t;

	var_t = (t_var *)prm->var;
	res = "";
	rmv = (t_token *)prm->tkn;
	join_vars_normf(var, &res);
	if (prm->flag)
		join_vars_norms(prm, head, curr, res);
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
		prm->flag = 1;
	}
}
