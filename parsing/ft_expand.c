/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/18 06:40:49 by aaghla           ###   ########.fr       */
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
	// printf("prompt in ft_trim = %s\tand start at %s\n", prompt, prompt +j);
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != 9
			&& prompt[i] != '"' && prompt[i] != '\'' && prompt[i] != '$')
	{
		i++;
		count++;
	}
	res = ft_malloc((count +1) * sizeof(char), 0);
	i = 0;
	while (prompt[j] && prompt[j] != ' ' && prompt[j] != 9
			&& prompt[j] != '"' && prompt[j] != '\'' && prompt[j] != '$')
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
	// while (prompt[i] && (prompt[i] == ' ' || prompt[i] == 9))
	// 	i++;
	while (prompt[j] && prompt[j] != '$')
		j++;
	prompt[j] = '\0';
	res = my_strdup(prompt + i);
	// free(prompt);
	
	// printf("res in get_rest = %s\n", res);
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
	value = ft_env_srch(var, &prm->env);
	if (value)
	{
		if (!*prompt)
			return (value);
		// printf("\tprompt = %s|\n\ti = %d|\n\tprompt + i= %s|\n", prompt, i, prompt +i);
		return (ft_strtrim(ft_strjoin(value, rest), "\'\""));
	}
	if (c == '"')
		return (ft_strtrim(rest, "\""));
	return ("\n");
}

// Get the characters before '$' if prompt is like (ggg$SHELL)
char	*get_prev(char *prompt)
{
	char	*prev;
	int		i;

	i = 0;
	while (prompt[i] && prompt[i] != '$')
		i++;
	prev = my_strdup(prompt);
	prev[i] = '\0';
	// printf("prev in get_prev = %s|\ni in get_prev = %d\n", prev, i);
	return (ft_strtrim(prev, "\'\""));
}

char	last_char(char *prompt)
{
	int	i;

	i = 0;
	while(prompt[i])
		i++;
	printf("last_char: %c\n", prompt[i -1]);
	return (prompt[i -1]);
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
	// if ((c == '\'' && last_char(prompt) != '\'') || (c == '"' && last_char(prompt) != '"'))
	printf("is here in ft_expand\n");
	if (c == '\'')
		return (ft_strtrim(prompt, "\'\""));
	prev = get_prev(prompt);
	while (prompt[++i])
	{
		if (prompt[i] == '$')
		{
			res = ft_strjoin(res, expand_it(prompt, prm, c, i));
			// printf("\nprompt in ft_expand = %s$\nAnd res = %s$\n\n", prompt+i, res);
		}
	}
	return (ft_strjoin(prev, res));
}
