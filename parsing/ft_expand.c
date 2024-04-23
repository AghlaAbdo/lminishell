/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/23 23:21:49 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//  get only the variable name
char	*ft_trim(char *prompt, int j)
{
	char	*res;
	int		i;
	int		count;

	i = j;
	count = 0;
	while (prompt[i] && (prompt[i] == '_' || (prompt[i] >= 'a' && prompt[i] <= 'z'))
		|| (prompt[i] >= 'A' && prompt[i] <= 'Z'))
	{
		i++;
		count++;
	}
	res = ft_malloc((count +1) * sizeof(char), 0);
	i = 0;
	while (prompt[j] && (prompt[j] == '_' || (prompt[j] >= 'a' && prompt[j] <= 'z'))
		|| (prompt[j] >= 'A' && prompt[j] <= 'Z'))
	{
		res[i] = prompt[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

// get the rest after the variable name till the end of the string or till the starting of another variable
char	*get_rest(char *prompt, int i)
{
	char	*res;
	int		j;

	j = i;
	prompt = my_strdup(prompt);
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != 9 && prompt[i] != '$')
		i++;
	while (prompt[j] && prompt[j] != '$')
		j++;
	prompt[j] = '\0';
	res = my_strdup(prompt + i);
	return (res);
}

char	*expand_it(char *prompt, t_parms *prm, char c, int i)
{
	char	*value;
	char	*var;
	char	*rest;

	var = ft_trim(prompt, i +1);
	rest = "";
	if (c == '"')
		rest = get_rest(prompt, i +1);
	printf("\nvar = %s\n\n", var);
	if (prompt[i +1] >= '0' && prompt[i +1] <= '9')
		return (ft_strjoin(prompt + (i + 2), rest));
	if (prompt[i +1] != '_' && !((prompt[i +1] >= 'a' && prompt[i +1] <= 'z')
		|| (prompt[i +1] >= 'A' && prompt[i +1] <= 'Z')))
		return (ft_strjoin(prompt +i, rest));
	value = ft_env_srch(var, &prm->env);
	if (value)
	{
		if (!*prompt)
			return (value);
		return (ft_strtrim(ft_strjoin(value, rest), "\'\""));
	}
	if (c == '"')
		return (ft_strtrim(rest, "\""));
	return ("");
}

// Get the characters before '$' if prompt is like (ggg$SHELL)
char	*get_prev(char *prompt, int i)
{
	prompt = my_strdup(prompt);
	prompt[i] = '\0';
	if (i)
		i--;
	while (i > 0 && prompt[i] != ' ' && prompt[i] != 9 && prompt[i] != '\n'
			&& prompt[i] != '$')
		i--;
	if (prompt[i] == '$')
	{
		i++;
		while (prompt[i] && (prompt[i] == '_' || (prompt[i] >= 'a' && prompt[i] <= 'z') || (prompt[i] >= 'A'
			&& prompt[i] <= 'Z') || (prompt[i] >= '0' && prompt[i] <= '9')))
			i++;
	}
	return (prompt +i);
}

char	*ft_expand(char *prompt, t_parms *prm)
{
	char	*res;
	char	*prev;
	char	c;
	int		i;

	res = "";
	if (*prompt == '"' || *prompt == '\'')
		c = *prompt;
	else
		c = 0;
	i = -1;
	if (c == '\'')
		return (ft_strtrim(prompt, "\'\""));
	// prev = get_prev(prompt);
	while (prompt[++i])
	{
		if (prompt[i] == '$')
		{
			res = ft_strjoin(res, ft_strjoin(get_prev(prompt, i), expand_it(prompt, prm, c, i)));
			// printf("\nprompt in ft_expand = %s$\nAnd res = %s$\n\n", prompt+i, res);
		}
	}
	return (res);
}
