/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:54:38 by thedon            #+#    #+#             */
/*   Updated: 2024/05/31 13:05:32 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_quote_closed(t_parms *prm, char *input)
{
	char	c;
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			c = input[i++];
			while (input[i] && input[i] != c)
				i++;
			if (input[i] != c)
			{
				printf("syntax error: unclosed quotes\n");
				prm->ext_stts = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_syntax(t_parms *prm, t_token *tkn)
{
	if (*tkn->token == '|')
	{
		prm->ext_stts = 258;
		printf("lminishell: syntax error near unexpected token\n");
		return (1);
	}
	while (tkn)
	{
		if (!tkn->type || (tkn->next && *tkn->next->token == '|'
				&& (*tkn->token == '>'
					|| *tkn->token == '<' || *tkn->token == '|'))
			|| ((tkn->type == '>' || tkn->type == '<') && (!tkn->next
					|| (tkn->next
						&& (tkn->next->type == '<' || tkn->next->type == '>'))))
			|| (tkn->type == '|' && !tkn->next))
		{
			prm->ext_stts = 258;
			printf("lminishell: syntax error near unexpected token\n");
			return (1);
		}
		if (!tkn->next)
			break ;
		tkn = tkn->next;
	}
	return (0);
}

int	is_too_long(t_parms *prm, int count)
{
	if (count > 500)
	{
		printf("lminishell: Resource temporarily unavailable\n");
		prm->ext_stts = 1;
		return (1);
	}
	return (0);
}

int	check_for_resources(char *input, t_parms *prm, int count, int i)
{
	char	c;

	while (input[i])
	{
		c = input[i];
		if (c == '"' || c == '\'')
		{
			while (input[++i] && input[i] != c)
				;
			i++;
		}
		if (input[i] == '|' && input[i +1] == '|')
		{
			prm->ext_stts = 258;
			printf("lminishell: syntax error near unexpected token\n");
			return (1);
		}
		else if (input[i] == '|')
			count++;
		i++;
	}
	if (is_too_long(prm, count))
		return (1);
	return (0);
}

t_sh	*ft_parser(char *input, t_parms *prms)
{
	t_sh	*res;
	t_token	*tkn;

	if (!input || !*input || is_quote_closed(prms, input))
		return (NULL);
	if (check_for_resources(input, prms, 0, 0))
		return (NULL);
	input = ft_strtrim(input, " \t");
	if (!input || !*input)
		return (NULL);
	tkn = parse_input(NULL, input, NULL, 0);
	if (check_syntax(prms, tkn))
		return (NULL);
	ft_expand(&tkn, prms, NULL, tkn);
	if (here_doc(tkn, prms))
		return (NULL);
	res = ft_tokenization(NULL, tkn, NULL, 0);
	return (res);
}
