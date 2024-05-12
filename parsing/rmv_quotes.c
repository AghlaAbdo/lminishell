/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmv_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:38:27 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/11 20:56:43 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	rmv_char(char *token)
{
	char	*res;
	char	c;

	res = token;
	while (*token)
	{
		if (*token == '\'' || *token == '"')
		{
			c = *token;
			token++;
			while (*token != c)
			{
				*res++ = *token++;
			}
			token++;
		}
		if (*token != '\'' && *token != '"')
		{
			*res = *token;
			res++;
			token++;
		}
	}
	*res = '\0';
}

void	rmv_quotes(t_token *tkn)
{
	while (tkn)
	{
		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<"))
			&& tkn->type != 'V' && (ft_strchr(tkn->token, '\'') || ft_strchr(tkn->token, '"')))
		{
			rmv_char(tkn->token);
		}
		tkn = tkn->next;
	}
}
