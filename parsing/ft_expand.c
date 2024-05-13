/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/13 17:06:01 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//  get only the variable name
char	*ft_trim(char *word, int j)
{
	char	*res;
	int		i;
	int		count;

	i = j;
	count = 0;
	while (word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
		|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))
	{
		i++;
		count++;
	}
	res = ft_malloc((count +1) * sizeof(char), 0);
	i = 0;
	while (word[j] && (word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z') || (word[j] >= '0' && word[j] <= '9'))
	{
		res[i] = word[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_n_var(t_parms *prm, char *word, char *var, int i)
{
	char	*cpy;
	char	*value;

	cpy = my_strdup(word);
	cpy[(i) +2] = '\0';
	cpy++;
	// exit(1);
	prm->len = ft_len(var);
	if (!prm->len)
	{
		printf("prm->len is 0?\n");
		prm->len = 2;
	}
	value = ft_env_srch(cpy, &prm->env);
	if (value)
		return(ft_strjoin(value,  word + i +2));
	// *l = 0;
	printf("word + i +2: [%s]\n", word + i +2);
	// printf("in var, word: [%s]\t word[%d]: %c\n", word, i, word[i]);
	return (word + i +2);
}

char	*split_value(t_token **tkn, char *value, char *bef, char *aft)
{
	char	**arr;
	char	*res;
	int		i;

	i = 0;
	printf("value in splie_value: [%s]\n", value);
	arr = my_split(value, ' ');
	rmv_char(bef);
	// rmv_char(aft);
	(*tkn)->token = ft_strjoin(bef, arr[i]);
	(*tkn)->type = 'V';
	while (arr[++i + 1] && (*tkn))
	{
		ft_token_insrt(tkn, ft_token_new(arr[i], 'V'));
		(*tkn) = (*tkn)->next;
	}
	res = ft_strjoin(arr[i], aft);
	printf("res after: [%s]\narr[%d]: [%s]\n", res, i,  arr[i]);
	ft_token_insrt(tkn, ft_token_new(res, 'B'));
	return (NULL);
}

char	*check_vlid_var(t_parms *prm, char *word, int i)
{
	char	*var;
	
	var = ft_trim(word, i +1);
	if (word[i +1] >= '0' && word[i +1] <= '9')
		return (get_n_var(prm, word, var, i));
	if (word[i +1] != '_' && !((word[i +1] >= 'a' && word[i +1] <= 'z')
		|| (word[i +1] >= 'A' && word[i +1] <= 'Z')))
	{
		prm->len = 2;
		return (word + i);
	}
	printf("\nvar = %s\n\n", var);
	if (!*var || *(word + i + 1) == '"')
		return (word + i +1);
	return (NULL);
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
	while (word[j] && (word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z')
		|| (word[j] >= '0' && word[j] <= '9'))
		j++;
	var = ft_env_srch(var, &prm->env);
	if (var && prm->c != '"' && (ft_strchr(var, ' ') || ft_strchr(var, '\t')))
		return (split_value(tkn, var, get_prev(word, i), word + j));
	if (var)
	{
		prm->len = ft_len(var);
		if (!word[j])
			return (var);
		res = ft_strjoin(var, word +j);
		return (res);
	}
	return (word +j);
}

char	*get_prev(char *word, int i)
{
	word = my_strdup(word);
	word[i] = '\0';
	return (word);
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
			(*token) = ft_strjoin(get_prev((*token), *i), res);
			while (prms->len-- > 1)
				(*i)++;
		}
		if ((*token)[*i] != '"' && (*token)[*i] != '$')
			(*i)++;
	}
	(*i)++;
	return (0);
}

void	skip_sngl_quot(char	*token, int *i)
{
	printf("token in skip token: [%s]\n", token + *i);
	if (token[*i] == '\'')
	{
		(*i)++;
		while (token[*i] && token[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	
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
			token = ft_strjoin(get_prev(token, i), res);
			while (prms->len-- > 1)
				i++;
		}
		if (token[i] && token[i] != '"' && token[i] != '$' && token[i] != '\'')
			i++;
	}
	return (token);
}

void	ft_expand(t_token **token, t_parms *prms)
{
	t_token	*tkn;
	char	*res;

	tkn = *token;
	while (tkn)
	{
		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<")) && ft_strchr(tkn->token, '$'))
		{
			res = expand_tkn(tkn, prms, tkn->token, 0);
			if (res)
				tkn->token = res;
		}
		tkn = tkn->next;
	}
}
