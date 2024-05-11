/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/11 16:58:47 by aaghla           ###   ########.fr       */
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

char	*get_n_var(t_parms *prm, char *word, char *var, int *i, int *l)
{
	char	*cpy;
	char	*value;

	cpy = my_strdup(word);
	cpy[(*i) +2] = '\0';
	cpy++;
	// exit(1);
	*l = ft_len(var);
	if (!*l)
	{
		printf("*L is 0?\n");
		*l = 2;
	}
	value = ft_env_srch(cpy, &prm->env);
	if (value)
		return(ft_strjoin(value,  word + *i +2));
	// *l = 0;
	printf("word + *i +2: [%s]\n", word + *i +2);
	// printf("in var, word: [%s]\t word[%d]: %c\n", word, *i, word[*i]);
	return (word + *i +2);
}

char	*split_value(t_token **tkn, char *value, char *bef, char *aft)
{
	char	**arr;
	char	*res;
	int		i;

	i = 0;
	printf("value in splie_value: [%s]\n", value);
	arr = my_split(value, ' ');
	(*tkn)->token = ft_strjoin(bef, arr[i]);
	while (arr[++i + 1] && (*tkn))
	{
		ft_token_insrt(tkn, ft_token_new(arr[i], 'V'));
		(*tkn) = (*tkn)->next;
	}
	res = ft_strjoin(arr[i], aft);
	printf("res after: [%s]\narr[%d]: [%s]\n", res, i,  arr[i]);
	ft_token_insrt(tkn, ft_token_new(res, 'V'));
	return (NULL);
}

char	*expand_it(t_token **tkn, char *word, t_parms *prm, int *i, int *l)
{
	char	*value;
	char	*var;
	char	*res;
	// char	*word;
	int		j;

	j = *i;
	*l = 0;
	// word = tkn->token;
	printf("word +i= [%c]\n", *(word + *i + 1));
	var = ft_trim(word, (*i) +1);
	printf("\nvar = %s\n\n", var);
	if (!*var || *(word + *i + 1) == '"')
	{
		// exit(1);
		// (*i)++;
		return (word + *i +1);
	}
	// sleep(3);
	printf("before word: [%s]\n", word);
	// (*i)++;
	// return (word);
	if (word[(*i) +1] >= '0' && word[(*i) +1] <= '9')
		return (get_n_var(prm, word, var, i, l));
	if (word[j +1] != '_' && !((word[j +1] >= 'a' && word[j +1] <= 'z')
		|| (word[j +1] >= 'A' && word[j +1] <= 'Z')))
	{
		(*i)++;
		return (word);
	}
	j++;
	while (word[j] && (word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
		|| (word[j] >= 'A' && word[j] <= 'Z') || (word[j] >= '0' && word[j] <= '9'))
		j++;
	value = ft_env_srch(var, &prm->env);
	if (value && (ft_strchr(value, ' ') || ft_strchr(value, '\t')))
		return (split_value(tkn, value, get_prev(word, *i), word +j));
	if (value)
	{
		*l = ft_len(value);
		if (!word[j])
		{
			printf("\t\twhy !*word?\n");
			return (value);
		}
		res = ft_strjoin(value, word +j);
		printf("value: [%s]\t res: [%s]\trest: [%s]\n", value, res, word +j);
		return (res);
	}
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

char	*expand_tkn(t_token *tkn, t_parms *prms, char c)
{
	int		i;
	int		len;
	char	*token;
	char	*res;

	token = tkn->token;
	i = 0;
	if (c == '"')
	{
		while (token[i])
		{
			if (token[i] == '"')
			{
				i++;
				while (token[i] && token[i] != '"')
				{
					if (token[i] == '$')
					{
						res = expand_it(&tkn, token, prms, &i, &len);
						if (!res)
							return (NULL);
						token = ft_strjoin(get_prev(token, i), res);
						printf("token after join: [%s]\n", token);
						while (len-- > 1)
							i++;
					}
					printf("token +i in expand_tkn: [%s]\n", token +i);
					if (token[i] != '"' && token[i] != '$')
						i++;
				}
				i++;
			}
			if (token[i] == '\'')
			{
				while (token[++i] && token[i] != '\'')
					;
				i++;
			}
			if (token[i] == '$')
			{
				res = expand_it(&tkn, token, prms, &i, &len);
					if (!res)
						return (NULL);
				token = ft_strjoin(get_prev(token, i), res);
				while (len-- > 1)
					i++;
			}
			if (token[i] && token[i] != '"' && token[i] != '$' && token[i] != '\'')
				i++;
		}
	}
	else
	{
		printf("sec expand\n");
		while (token[i])
		{
			if (token[i] == '$')
			{
				res = expand_it(&tkn, token, prms, &i, &len);
					if (!res)
						return (NULL);
				token = ft_strjoin(get_prev(token, i), res);
				while (len-- > 1)
					i++;
			}
			if (token[i] && token[i] != '$')
				i++;
			
		}
	}
	return (token);
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
	t_token	*tkn;
	char	*res;

	tkn = *token;
	while (tkn)
	{
		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<")) && ft_strchr(tkn->token, '$'))
		{
			res = expand_tkn(tkn, prms, '"');
			if (res)
				tkn->token = res;
			
		}
		tkn = tkn->next;
	}
}
