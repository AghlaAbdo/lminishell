/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/29 23:47:01 by aaghla           ###   ########.fr       */
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

// get the rest after the variable name till the end of the string or till the starting of another variable
char	*get_rest(char *word)
{
	int	i;

	i = 0;
	word = my_strdup(word);
	// i = 1;
	printf("word in get_rest: %s|\n", word);
	// if (!(word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
	// 	|| (word[i] >= 'A' && word[i] <= 'Z'))  || (word[i] >= '0' && word[i] <= '9'))
	// {
	// 	while (word[i] && word[i] != '$')
	// 		i++;
	// 	word[i] = '\0';
	// 	if (word[1] >= '0' && word[1] <= '9')
	// 		return (word +2);
	// 	else
	// 		return (word);
	// }
	// i = 1;
	while (word[i] && word[i] != '$')
		i++;
	word[i] = '\0';
	// i = 1;
	// while (word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
	// 	|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))
	// 	i++;
	return (word);
}

// char	*invalid_var(char *prompt, int i)

char	*expand_it(char *word, t_parms *prm, char c, int i)
{
	char	*value;
	char	*var;
	char	*rest;

	var = ft_trim(word, i +1);
	rest = "";
	// if (c == '"')
	printf("\nvar = %s\n\n", var);
	// if (word[i +1] >= '0' && word[i +1] <= '9')
	// 	return (ft_strtrim(get_rest(word, c, i), "\""));
	// if (word[i +1] != '_' && !((word[i +1] >= 'a' && word[i +1] <= 'z')
	// 	|| (word[i +1] >= 'A' && word[i +1] <= 'Z')))
	// 	return (get_rest(word, c, i));
	i++;
	while (word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
		|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))
		i++;
	rest = get_rest(word + i);
	value = ft_env_srch(var, &prm->env);
	if (value)
	{
		printf("value: [%s]\t rest: [%s]\n", value, rest);
		// if (!*word)
		// {
		// 	printf("\t\twhy !*word?\n");
		// 	return (value);
		// }
		return (ft_strjoin(value, rest));
	}
	// if (c == '"')
	// 	return (ft_strtrim(rest, "\""));
	return (rest);
}

// Get the characters before '$' if word is like (ggg$SHELL)
char	*get_prev(char *word, int i)
{
	word = my_strdup(word);
	// if (i)
	// 	i--;
	// while (i > 0 && word[i] != '$')
	// 	i--;
	// if (word[i] == '$')
	// {
	// 	i++;
		while (word[i] && word[i] != '$')
			i++;
	// }
	word[i] = '\0';
	printf("word in get_prev: [%s]\n", word);
	return (word);
}

// char	*get_prev(char *word, int i)
// {
// 	word = my_strdup(word);
// 	word[i] = '\0';
// 	if (i)
// 		i--;
// 	while (i > 0 && word[i] != '$')
// 		i--;
// 	if (word[i] == '$')
// 	{
// 		i++;
// 		while (word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A'
// 			&& word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9')))
// 			i++;
// 	}
// 	return (word +i);
// }

void	expand_quotes(t_token *tkn, t_parms *prms)
{
	char	*prev;
	char	*rest;
	char	*res;
	int		i;

	i = 0;
	res = "";
	prev = get_prev(tkn->token, i);
	printf("prev = [%s]\n", prev);
	while (tkn->token[i])
	{
		if (tkn->token[i] == '$')
		{
			res = ft_strjoin(res, expand_it(tkn->token, prms, 0, i));
			printf("res = [%s]\n", res);
		}
		i++;
	}
	res = ft_strjoin(prev, res);
	if (*res)
	tkn->token = res;
}

void	ft_expand(t_token **token, t_parms *prms)
{
	char	*res;
	char	*prev;
	char	c;
	int		i;
	t_token	*tkn;

	tkn = *token;
	while (tkn)
	{
		if (ft_strchr(tkn->token, '\'') || ft_strchr(tkn->token, '"') && ft_strchr(tkn->token, '$'))
			expand_quotes(tkn, prms);
		tkn = tkn->next;
	}


	// res = "";
	// if (*word == '"' || *word == '\'')
	// 	c = *word;
	// else
	// 	c = 0;
	// i = -1;
	// if (c == '\'')
	// 	return (ft_strtrim(word, "\'\""));
	// // prev = get_prev(word);
	// while (word[++i])
	// {
	// 	if (word[i] == '$')
	// 	{
	// 		res = ft_strjoin(res, ft_strjoin(get_prev(word, i), expand_it(word, prm, c, i)));
	// 		// printf("\nword in ft_expand = %s$\nAnd res = %s$\n\n", word+i, res);
	// 	}
	// }
	// return (res);
}
