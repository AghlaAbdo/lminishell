/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/21 11:10:30 by aaghla           ###   ########.fr       */
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
	if (word[i] == '?')
		return ("$?");
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
		res[i++] = word[j++];
	res[i] = '\0';
	return (res);
}

static char	*expand_here(char *word, t_parms *prm, int i)
{
	char	*value;
	char	*var;
	char	*res;
	int		j;

	j = i +1;
	var = ft_trim(word, j);
	res = check_vlid_var(prm, word, i, &j);
	if (res)
		return (res);
	value = ft_env_srch(var, &prm->env);
	if (value)
	{
		prm->len = ft_len(value);
		if (!word[j])
			return (value);
		res = ft_pstrjoin(value, word + j);
		return (res);
	}
	return (word + j);
}

char	*expand_heredoc(char *token, t_parms *prms)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			prms->len = 0;
			token = ft_pstrjoin(get_prev(token, i),
					expand_here(token, prms, i));
			while (prms->len-- > 1)
				i++;
		}
		if (token[i] && token[i] != '$')
			i++;
	}
	return (token);
}
