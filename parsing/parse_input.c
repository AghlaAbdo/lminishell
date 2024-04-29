/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 06:44:23 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/29 16:38:38 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	check_end(char *input, int i)
// {
	
// }

char	*get_token(char *str, int j)
{
	// int	i;

	// i = 0;
	// printf("str in get_token: %s|\tstr[%d]: %c\n", str, j, str[j]);
	str = my_strdup(str);
	str[j] = '\0';
	return (str);
}

char	check_word(char *word)
{
	if (!ft_strcmp(word, ">") || !ft_strcmp(word, ">>"))
		return ('>');
	else if (!ft_strcmp(word, "<") || !ft_strcmp(word, "<<"))
		return ('<');
	else if (!ft_strcmp(word, "|"))
		return ('|');
	return (0);
}

void	get_rest_word(char *input, int *i, int *j)
{
	char	c;
	
	while (input[*i] && input[*i] != ' ' && input[*i] != 9
		&& input[*i] != '>' && input[*i] != '<' && input[*i] != '|')
		{
			(*i)++;
			if (input[*i] == '"' || input[*i] == '\'')
			{
				c = input[(*i)++];
				while (input[*i] && input[*i] != c)
					(*i)++;
			}
		}
	
}

void	get_word(t_token **token, char *input, int *i, int *j)
{
	char	c;
	
	while (input[*i] && input[*i] != '>' && input[*i] != '<'
		&& input[*i] != '|' && input[*i] != ' ' && input[*i] != 9)
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			c = input[*i];
			while (*i >= 0 && input[*i] != ' ' && input[*i] != 9
				&& input[*i] != '>' && input[*i] != '<' && input[*i] != '|')
					(*i)--;
			(*i)++;
			*j = *i;
			while (input[*i] && input[*i] != c)
				(*i)++;
			while (input[++(*i)] && input[*i] != c)
				;
			get_rest_word(input, i, j);
			ft_token_addb(token, ft_token_new(get_token(input +*j, *i -*j), 'w'));
			*j = *i;
			break ;
		}
		(*i)++;
	}
}

// void	parse_word(t_token **token, char *input, char *word, int i)
// {
// 	char	c;
// 	int		j;

// 	while (input[i])
// 	{
// 		j = i;
// 		get_word(token, input, &i, &j);
// 		if (j != i)
// 			ft_token_addb(token, ft_token_new(get_token(input +j, i -j), 'S'));
// 		while (input[i] && (input[i] == ' ' || input[i] == 9))
// 			i++;
// 		c = input[i];
// 		j = i;
// 		if (c == '>' || c == '<' || c == '|')
// 		{
// 			while (input[i] && input[i] == c)
// 				i++;
// 			word = get_token(input + j, i -j);
// 			ft_token_addb(token, ft_token_new(word, check_word(word)));
// 		}
// 		while (input[i] && (input[i] == ' ' || input[i] == 9))
// 			i++;
// 	}
// }

t_token	*parse_input(t_token *token, char *input, char *word, int i)
{
	char	c;
	int		j;

	while (input[i])
	{
		j = i;
		get_word(&token, input, &i, &j);
		if (j != i)
			ft_token_addb(&token, ft_token_new(get_token(input +j, i -j), 'S'));
		while (input[i] && (input[i] == ' ' || input[i] == 9))
			i++;
		c = input[i];
		j = i;
		if (c == '>' || c == '<' || c == '|')
		{
			while (input[i] && input[i] == c)
				i++;
			word = get_token(input + j, i -j);
			ft_token_addb(&token, ft_token_new(word, check_word(word)));
		}
		while (input[i] && (input[i] == ' ' || input[i] == 9))
			i++;
	}
	return (token);
}
