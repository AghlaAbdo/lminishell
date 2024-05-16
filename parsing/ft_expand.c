/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/16 15:30:15 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*split_value(t_token **tkn, char *value, char *bef, char *aft)
{
	char	**arr;
	int		i;

	i = 0;
	arr = my_split(value, ' ');
	if ((*tkn)->type == 'L')
	{
		while ((*tkn)->lst_len)
		{
			i++;
			(*tkn)->lst_len--;
		}
	}
	rmv_char(bef + i);
	i = 0;
	(*tkn)->token = ft_pstrjoin(bef, arr[i]);
	(*tkn)->type = 'V';
	while (arr[++i + 1] && (*tkn))
	{
		ft_token_insrt(tkn, ft_token_new(arr[i], 'V', 0));
		(*tkn) = (*tkn)->next;
	}
	value = ft_pstrjoin(arr[i], aft);
	ft_token_insrt(tkn, ft_token_new(value, 'L', ft_len(arr[i])));
	return (NULL);
}

int	check_splt(t_token *tkn)
{
	t_token	*prv;
	t_token	*curr;

	prv = tkn;
	curr = tkn;
	while (prv && prv->prev)
	{
		printf("prv token: [%s]\tprev: [%s]\n", prv->token, prv->prev->token);
		if (!prv->prev || prv->prev->type == '|')
			break;
		prv = prv->prev;
	}
	while (prv && prv != tkn)
	{
		printf("next token: [%s]\n", prv->token);
		if (prv->type == '<' || prv->type == '>')
			prv = prv->next->next;
		else
		{
		printf("here\n");
			if (!ft_strcmp(prv->token, "export"))
			{
				prv = curr;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}

char	*expand_it(t_token **tkn, char *word, t_parms *prm, int i)
{
	char	*var;
	char	*res;
	int		j;

	j = i +1;
	var = ft_trim(word, i +1);
	res = check_vlid_var(prm, word, i);
	if (res)
		return (res);
	while (word[j] && ((word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z')
		|| (word[j] >= '0' && word[j] <= '9')))
		j++;
	var = ft_env_srch(var, &prm->env);
	if (var && prm->c != '"' && (ft_strchr(var, ' ') || ft_strchr(var, '\t')))
		return (split_value(tkn, var, get_prev(word, i), word + j));
	if (var)
	{
		prm->len = ft_len(var);
		if (!word[j])
			return (var);
		res = ft_pstrjoin(var, word + j);
		return (res);
	}
	return (word + j);
}

int	expand_quotes(t_parms *prms, char **token, int *i)
{
	char	*res;

	prms->word = *token;
	(*i)++;
	while ((*token)[*i] && (*token)[*i] != '"')
	{
		if ((*token)[*i] == '$')
		{
			prms->len = 0;
			prms->c = '"';
			res = expand_it(NULL, *token, prms, *i);
			if (!res)
				return (1);
			(*token) = ft_pstrjoin(get_prev((*token), *i), res);
			while (prms->len-- > 1)
				(*i)++;
		}
		if ((*token)[*i] != '"' && (*token)[*i] != '$')
			(*i)++;
	}
	(*i)++;
	return (0);
}

char	*expand_tkn(t_token *tkn, t_parms *prms, char *token, int i)
{
	char	*res;

	while (token[i])
	{
		if (token[i] == '"')
			if (expand_quotes(prms, &token, &i))
				return (NULL);
		skip_sngl_quot(token, &i);
		if (token[i] == '$')
		{
			prms->len = 0;
			prms->c = 0;
			res = expand_it(&tkn, token, prms, i);
			if (!res)
				return (NULL);
			token = ft_pstrjoin(get_prev(token, i), res);
			while (prms->len-- > 1)
				i++;
		}
		if (token[i] && token[i] != '"' && token[i] != '$' && token[i] != '\'')
			i++;
	}
	return (token);
}

// expand token, 'i' skips the last splited var token (ex: d")
// I still need to skip it again in get_prev so I used 'j'
void	ft_expand(t_token **token, t_parms *prms)
{
	t_token	*tkn;
	char	*res;
	int		i;
	int		j;

	tkn = *token;
	while (tkn)
	{
		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<"))
			&& ft_strchr(tkn->token, '$'))
		{
			i = 0;
			res = tkn->token;
			if (tkn->type == 'L')
			{
				j = tkn->lst_len +1;
				while (--j)
					i++;
			}
			res = expand_tkn(tkn, prms, res, i);
			if (res)
				tkn->token = res;
		}
		tkn = tkn->next;
	}
}
