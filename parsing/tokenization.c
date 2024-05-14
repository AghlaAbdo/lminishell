/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:22:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/14 18:48:46 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_in(t_sh **sh, t_token *tkn)
{
	t_rdr	*rdr;

	rdr = NULL;
	while (tkn && tkn->type != '|')
	{
		if (tkn->type == '<' || tkn->type == '>')
		{
			ft_rdr_addb(&rdr, ft_rdr_new(tkn->next->token, tkn->token));
		}
		tkn = tkn->next;
	}
	ft_sh_addb(sh, ft_sh_new(rdr, NULL, "REDIR"));
}

int	count_cmd(t_token *tkn)
{
	int	count;

	count = 0;
	while (tkn && tkn->type != '|')
	{
		if ((!tkn->prev && tkn->type != '<' && tkn->type != '>')
			|| (tkn->prev && tkn->prev->type != '<' && tkn->prev->type != '>'
				&& tkn->type != '<' && tkn->type != '>'))
			count++;
		tkn = tkn->next;
	}
	return (count);
}

t_sh	*ft_tokenization(t_sh *sh, t_token *tkn, char **cmd, int i)
{
	while (tkn)
	{
		add_in(&sh, tkn);
		cmd = (char **)ft_malloc((count_cmd(tkn) + 1) * sizeof(char *), 0);
		i = 0;
		while (tkn && tkn->type != '|')
		{
			if ((!tkn->prev && tkn->type != '<' && tkn->type != '>')
				|| (tkn->prev && tkn->prev->type != '<'
					&& tkn->prev->type != '>'
					&& tkn->type != '<' && tkn->type != '>'))
				cmd[i++] = tkn->token;
			tkn = tkn->next;
			cmd[i] = NULL;
			if (cmd[0] && (!tkn || tkn->type == '|'))
				ft_sh_addb(&sh, ft_sh_new(NULL, cmd, "CMD"));
		}
		if (tkn && tkn->type == '|')
			ft_sh_addb(&sh, ft_sh_new(NULL, &tkn->token, "PIPE"));
		if (tkn)
			tkn = tkn->next;
	}
	return (sh);
}
