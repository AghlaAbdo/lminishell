/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:11:49 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/07 16:07:44 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	read_heredoc(t_token *tkn, t_parms *prm, char *limit, int quots)
{
	char	*line;
	char	*res;

	res = "";
	if (ft_strchr(limit, '"') || ft_strchr(limit, '\''))
		quots = 1;
	rmv_char(limit);
	while (1)
	{
		line = readline("> ");
		printf("line = [%s]\n", line);
		if (!line || !ft_strcmp(line, limit))
			break;
		res = ft_strjoin(ft_strjoin(res, line), "\n");
		free(line);
	}
	free(line);
	if (!quots)
	{
		printf("res after add_quotes: [%s]\n", res);
		tkn->next->token = expand_tkn(res, prm, '\'');
	}
	else
		tkn->next->token = res;
}

void	here_doc(t_token *tkn, t_parms *prm)
{
	int	i;

	while (tkn)
	{
		if (tkn->type == '<' && ft_len(tkn->token) > 1)
		{
			read_heredoc(tkn, prm, tkn->next->token, 0);
		}
		tkn = tkn->next;
	}
}
