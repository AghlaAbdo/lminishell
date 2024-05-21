/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:07:30 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/21 12:50:56 by aaghla           ###   ########.fr       */
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

int	dollar_var(char *wd, int *i)
{
	int	j;

	j = 0;
	while (wd[j] && wd[j] == '$')
	{
		j++;
		(*i)++;
	}
	if (!wd[j])
		return (1);
	(*i)--;
	return (0);
}

char	*check_vlid_var(t_parms *prm, char *wd, int i, int *j)
{
	char	*var;

	if (dollar_var(wd + i, &i))
		return ("");
	var = ft_trim(wd, i +1);
	while (wd[*j] && ((wd[*j] == '_' || (wd[*j] >= 'a' && wd[*j] <= 'z'))
			|| (wd[*j] >= 'A' && wd[*j] <= 'Z')
			|| (wd[*j] >= '0' && wd[*j] <= '9')))
		(*j)++;
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

int	check_splt(t_token *tkn)
{
	t_token	*prv;

	prv = tkn;
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
