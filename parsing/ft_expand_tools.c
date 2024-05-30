/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:07:30 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/30 19:44:36 by aaghla           ###   ########.fr       */
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
	(void)prm;
	while (wd[j] && wd[j] == '$')
	{
		j++;
		(*i)++;
	}
	if (!wd[j] && j == 1 && (!var->next || var->next->is_f))
	{
		if (var->next)
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

char	*check_vlid_var(t_parms *prm, char *wd, int i, int *j)
{
	char	*var;
	char	*res;

	res = dollar_var(prm, wd + i, &i);
	if (res)
	{
		return (res);
	}
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
