/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/02 19:05:15 by aaghla           ###   ########.fr       */
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
// char	*get_rest(char *word, char c)
// {
// 	int	i;

// 	i = 0;
// 	word = my_strdup(word);
// 	// i = 1;
// 	printf("word in get_rest: %s|\n", word);
// 	// if (!(word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
// 	// 	|| (word[i] >= 'A' && word[i] <= 'Z'))  || (word[i] >= '0' && word[i] <= '9'))
// 	// {
// 	// 	while (word[i] && word[i] != '$')
// 	// 		i++;
// 	// 	word[i] = '\0';
// 	// 	if (word[1] >= '0' && word[1] <= '9')
// 	// 		return (word +2);
// 	// 	else
// 	// 		return (word);
// 	// }
// 	// i = 1;
// 	// if (c == '\'')
// 	// {
// 	// 	while (word[i] && word[i] != '\'')
// 	// 		i++;
// 	// 	if (word[i])
// 	// 		i++;
// 	// }
// 	// else
// 	while (word[i] && word[i] != '$')
// 	{
// 		if (c == '\'' && word[i] == c)
// 		{
// 			i++;
// 			while (word[i] && word[i] != c)
// 				i++;
// 		}
// 		i++;
// 	}
// 	word[i] = '\0';
// 	// i = 1;
// 	// while (word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
// 	// 	|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))
// 	// 	i++;
// 	printf("rest in get_rest: [%s]\n", word);
// 	return (word);
// }

// char	*invalid_var(char *prompt, int i)

char	*expand_it(char *word, t_parms *prm, int *i, int *l)
{
	char	*value;
	char	*var;
	char	*rest;
	char	*res;
	int		j;

	j = *i;

	var = ft_trim(word, (*i) +1);
	rest = "";
	// if (c == '"')
	printf("\nvar = %s\n\n", var);
	// if (word[i +1] >= '0' && word[i +1] <= '9')
	// 	return (ft_strtrim(get_rest(word, c, i), "\""));
	// if (word[i +1] != '_' && !((word[i +1] >= 'a' && word[i +1] <= 'z')
	// 	|| (word[i +1] >= 'A' && word[i +1] <= 'Z')))
	// 	return (get_rest(word, c, i));
	// i++;
	// while (word[i] && (word[i] == '_' || (word[i] >= 'a' && word[i] <= 'z'))
	// 	|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))
	// 	i++;
	// rest = get_rest(word + *i, c);
	j++;
	while (word[j] && (word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z') || (word[j] >= '0' && word[j] <= '9'))
		printf("skipped word[%d]: %c\n", j, word[j++]);
	value = ft_env_srch(var, &prm->env);
	if (value)
	{
		int le = ft_len(value);
		*l = ft_len(value);
		if (!word[j])
		{
			printf("\t\twhy !*word?\n");
			return (value);
		}
		res = ft_strjoin(value, word +j);
		// while (le--)
		// 	printf("\tskipped token[%d]: [%c]\n", *i, res[(*i)++]);
		// rest = get_rest(word + j, '"');
		printf("value: [%s]\t res: [%s]\trest: [%s]\n", value, res, word +j);
		return (res);
	}
	*l = 0;
	// if (c == '"')
	// 	return (ft_strtrim(rest, "\""));
	return (word +j);
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
	// while (word[i] && word[i] != '$')
	// {
	// 	if (word[i] == '\'')
	// 	{
	// 		while (word[i] && word[i] != '\'')
	// 			i++;
	// 		if (word[i])
	// 			i++;
	// 	}
	// 	i++;
	// }
	// // }
	// word[i] = '\0';
	// printf("word in get_prev: [%s]\n", word);
	word[i] = '\0';
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

// char	*get_rest(char *word, char c)
// {
	
// }

// char	*join_res(char *word, int i, char *res)
// {
	
// }

void	expand_quotes(t_token *tkn, t_parms *prms)
{
	int		i;
	int		len;

	i = 0;
	while (tkn->token[i])
	{
		if (tkn->token[i] == '"')
		{
			i++;
			while (tkn->token[i] != '"')
			{
				if (tkn->token[i] == '$')
				{
					tkn->token = ft_strjoin(get_prev(tkn->token, i), expand_it(tkn->token, prms, &i, &len));
					while (len-- > 1)
						i++;
				}
				i++;
			}
			i++;
		}
		if (tkn->token[i] == '\'')
		{
			while (tkn->token[++i] && tkn->token[i] != '\'')
				;
			i++;
			printf("index:[%d]: [%c]\n",i,  tkn->token[i]);
		}
		
		if (tkn->token[i] == '$')
		{
			tkn->token = ft_strjoin(get_prev(tkn->token, i), expand_it(tkn->token, prms, &i, &len));
			while (len-- > 1)
				i++;
		}
		if (tkn->token[i] != '"')
		i++;
	}
}

// void	expand_quotes(t_token *tkn, t_parms *prms)
// {
// 	char	*prev;
// 	char	*rest;
// 	char	*res;
// 	char	c;
// 	int		i;

// 	i = 0;
// 	res = "";
// 	prev = get_prev(tkn->token, i);
// 	printf("prev = [%s]\n", prev);
// 	while (tkn->token[i])
// 	{
// 		if (tkn->token[i] == '"')
// 		{
// 			c = tkn->token[i++];
// 			while (tkn->token[i] && tkn->token[i] != c)
// 			{
// 				if (tkn->token[i] == '$')
// 				{
// 					res = ft_strjoin(res, expand_it(tkn->token, prms, '"', i));
// 					printf("res = [%s]\n", res);
// 				}
// 				i++;
// 			}
// 			i++;
// 		}
// 		if (tkn->token[i] == '\'')
// 		{
// 			while (tkn->token[++i] && tkn->token[i] != '\'' && tkn->token[i] != '$')
// 				;
// 			res = ft_strjoin(res, get_rest(tkn->token +i, '\''));
// 			while (tkn->token[i] && tkn->token[i] != '\'')
// 				i++;
// 			i++;
// 		}
// 		if (tkn->token[i] == '$')
// 		{
// 			res = ft_strjoin(res, expand_it(tkn->token, prms, '"', i));
// 			printf("res = [%s]\n", res);
// 		}
// 		i++;
// 	}
// 	res = ft_strjoin(prev, res);
// 	if (*res)
// 	tkn->token = res;
// }

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
		// if (ft_strchr(tkn->token, '\'') || ft_strchr(tkn->token, '"') && ft_strchr(tkn->token, '$'))
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
