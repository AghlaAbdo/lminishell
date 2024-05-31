/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:07:30 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/31 11:01:35 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_n_var(t_parms *prm, char *word, char *var, int i)
{
	char	*cpy;
	char	*value;

	cpy = my_strdup(word);
	cpy[(i) +2] = '\0';
	cpy++;
	prm->len = ft_len(var);
	if (!prm->len)
		prm->len = 2;
	value = ft_env_srch(cpy, &prm->env);
	if (value)
		return (ft_pstrjoin(value, word + i +2));
	return (word + i + 2);
}

char	*get_prev(char *word, int i)
{
	char	tmp;
	char	*res;

	tmp = word[i];
	word[i] = '\0';
	res = my_strdup(word);
	word[i] = tmp;
	return (res);
}

char	*dollar_var(t_parms *prm, char *wd, int *i)
{
	t_var	*var;
	int		j;

	var = (t_var *)prm->var;
	j = 0;
	while (wd[j] && wd[j] == '$')
	{
		j++;
		(*i)++;
	}
	if (!wd[j] && j == 1 && (!var->next || var->next->is_f))
	{
		prm->len = j +1;
		return ("$");
	}
	if (!wd[j])
	{
		prm->len = j + 1;
		return ("");
	}
	(*i)--;
	return (NULL);
}

void	skip_var_name(char *wd, int *j)
{
	while (wd[*j] && ((wd[*j] == '_' || (wd[*j] >= 'a' && wd[*j] <= 'z'))
			|| (wd[*j] >= 'A' && wd[*j] <= 'Z')
			|| (wd[*j] >= '0' && wd[*j] <= '9')))
		(*j)++;
}

int	check_splt(t_token *tkn, char *value)
{
	t_token	*prv;

	prv = tkn;
	if (!ft_strchr(value, ' ') && !ft_strchr(value, 9))
		return (1);
	while (prv && prv->prev)
	{
		if (!prv->prev || prv->prev->type == '|')
			break ;
		prv = prv->prev;
	}
	while (prv && prv != tkn)
	{
		if (prv->type == '<' || prv->type == '>')
			prv = prv->next->next;
		else
		{
			if (!ft_strcmp(prv->token, "export"))
				return (1);
			else
				return (0);
		}
	}
	return (0);
}
