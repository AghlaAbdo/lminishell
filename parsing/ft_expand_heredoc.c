/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/17 11:34:17 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_here(char *word, t_parms *prm, int i)
{
	char	*value;
	char	*var;
	char	*res;
	int		j;

	j = i +1;
	var = ft_trim(word, j);
	res = check_vlid_var(prm, word, i);
	if (res)
		return (res);
	while (word[j] && ((word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z')
		|| (word[j] >= '0' && word[j] <= '9')))
		j++;
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
			token = ft_pstrjoin(get_prev(token, i, 0), expand_here(token, prms, i));
			while (prms->len-- > 1)
				i++;
		}
		if (token[i] && token[i] != '$')
			i++;
	}
	return (token);
}
