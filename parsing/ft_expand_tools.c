/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:07:30 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/16 21:09:56 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_trim(char *word, int j)
{
	char	*res;
	int		i;
	int		count;

	i = j;
	count = 0;
	while (word[i] && ((word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
		|| (word[i] >= 'A' && word[i] <= 'Z')
		|| (word[i] >= '0' && word[i] <= '9')))
	{
		i++;
		count++;
	}
	res = ft_malloc((count +1) * sizeof(char), 0);
	i = 0;
	while (word[j] && ((word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z')
		|| (word[j] >= '0' && word[j] <= '9')))
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
	prm->len = ft_len(var);
	if (!prm->len)
		prm->len = 2;
	value = ft_env_srch(cpy, &prm->env);
	if (value)
		return (ft_pstrjoin(value, word + i +2));
	return (word + i + 2);
}

void	skip_sngl_quot(char	*token, int *i)
{
	if (token[*i] == '\'')
	{
		(*i)++;
		while (token[*i] && token[*i] != '\'')
			(*i)++;
		(*i)++;
	}
}

char	*get_prev(char *word, int i, char c)
{
	char	*res;
	int		j;

	if (i >= 0)
	{
		word = my_strdup(word);
		word[i] = '\0';
	}
	res = word;
	j = 0;
	i = 0;
	printf("get_prev word:[%s]\n", word);
	if (c == '"')
	{
		while (word[i])
		{
			if (word[i] == '"')
			{
				i++;
				while (word[i] && word[i] != '"')
					res[j++] = word[i++];
			}
			while (word[i] && word[i] != '"')
			{
				if (word[i] == '\'')
				{
					c = word[i++];
					while (word[i] != c)
						res[j++] = word[i++];
					i++;
				}
				if (word[i] && word[i] != '\'' && word[i] != '"')
					res[j++] = word[i++];
			}
		}
	}
	else
	{
		while (word[i])
		{
			if (word[i] == '\'' || word[i] == '"')
			{
				c = word[i++];
				while (word[i] != c)
					res[j++] = word[i++];
				i++;
			}
			if (word[i] && word[i] != '\'' && word[i] != '"')
				res[j++] = word[i++];
			
		}
	}
	res[j] = '\0';
	printf("res after all: [%s]\n", res);
	return (res);
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
	if (!*var || *(word + i + 1) == '"')
		return (word + i +1);
	return (NULL);
}
