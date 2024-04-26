/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 06:44:23 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/26 20:06:04 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	check_end(char *input, int i)
// {
	
// }

char	*get_word(char *str, int j)
{
	// int	i;

	// i = 0;
	// printf("str in get_word: %s|\tstr[%d]: %c\n", str, j, str[j]);
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
	return ('0');
}

void	parse_word(t_token **token, char *prompt, char *word, int i)
{
	char	c;
	int		j;

	while (prompt[i])
	{
		j = i;
		while (prompt[i] && prompt[i] != '>' && prompt[i] != '<'
			&& prompt[i] != '|' && prompt[i] != ' ' && prompt[i] != 9)
		{
			if (prompt[i] == '\'' || prompt[i] == '\"')
			{
				c = prompt[i];
				while (i && prompt[i] != ' ' && prompt[i] != 9
					&& prompt[i] != '>' && prompt[i] != '<' && prompt[i] != '|')
					i--;
				i++;
				j = i;
				if (prompt[i] != c)
					while (prompt[i] && prompt[i] != c)
						i++;
				while (prompt[++i] && prompt[i] != c)
					;
				if (prompt[i] == c)
					while (prompt[i] && prompt[i] != ' ' && prompt[i] != 9
						&& prompt[i] != '>' && prompt[i] != '<' && prompt[i] != '|')
						i++;
				ft_token_addb(token, ft_token_new(get_word(prompt +j, i -j), 'w'));
				j = i;
				break ;
			}
			i++;
		}
		if (j != i)
			ft_token_addb(token, ft_token_new(get_word(prompt +j, i -j), 'S'));
		while (prompt[i] && (prompt[i] == ' ' || prompt[i] == 9))
			i++;
		c = prompt[i];
		j = i;
		// if (c == '\'' || c == '"')
		// {
		// 	i++;
		// 	while (prompt[i] && prompt[i] != c)
		// 		i++;
		// 	i++;
		// 	ft_token_addb(token, ft_token_new(get_word(prompt +j, i -j), 's'));
		// 	c = 0;
		// }
		
		if (c == '>' || c == '<' || c == '|')
		{
			while (prompt[i] && prompt[i] == c)
				i++;
			word = get_word(prompt + j, i -j);
			if (*word)
				ft_token_addb(token, ft_token_new(word, check_word(word)));
			
		}
		while (prompt[i] && (prompt[i] == ' ' || prompt[i] == 9))
			i++;
			
	}
}

t_token	*parse_input(char **prompt, char *input, t_parms *prms)
{
	t_token	*token;

	token = NULL;
	// while (*prompt)
	// {
		// if (**prompt == '"')
		// 	ft_token_addb(&token, ft_token_new(*prompt, 'r'));
		// else
			parse_word(&token, input, NULL, 0);
		*prompt++;
	// }
	while (token)
	{
		printf("token: [%s]\ttype: %c%%\n", token->token, token->type);
		token = token->next;
	}
	return (NULL);
}
