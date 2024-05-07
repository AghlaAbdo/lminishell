/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:22:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/07 21:01:09 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_sh	*ft_tokenization(t_token *tkn)
{
	t_sh	*sh;
	t_token	*curr;
	t_token	*end;

	sh = NULL;
	while (tkn)
	{
		curr = tkn;
		while (curr && curr->type != '|')
		{
			printf("skipped [%s]\n", curr->token);
			curr = curr->next;
		}
		if (curr)
			curr = curr->prev;
		while (curr && curr != tkn->prev)
		{
			printf("back to [%s]\n", curr->token);
			if (curr->prev && curr->prev->type == '<')
			{
				ft_sh_addb(&sh, ft_sh_new(&curr->prev->token, "REDIR"));
				if (!ft_strcmp(curr->token, "<<"))
					ft_sh_addb(&sh, ft_sh_new(&curr->token, "HERE"));
				else
					ft_sh_addb(&sh, ft_sh_new(&curr->token, "FILE"));
				break;
			}
			curr = curr->prev;
		}
		while (tkn && tkn->type != '|')
		{
			printf("tkn skipped [%s]\n", tkn->token);
			if (tkn->prev && tkn->prev->type != '<' && tkn->prev->type != '>'
				&& tkn->type != '<' && tkn->type != '>')
			{
				ft_sh_addb(&sh, ft_sh_new(&tkn->token, "CMD"));
			}
			tkn = tkn->next;
		}
		if (tkn && tkn->type == '|')
			ft_sh_addb(&sh, ft_sh_new(&tkn->token, "PIPE"));
		if (tkn && tkn->type == '|')
			tkn = tkn->next;
	}
	return (sh);
}
