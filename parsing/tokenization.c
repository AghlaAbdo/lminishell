/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:22:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/24 10:54:34 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_rdr	*add_in(t_sh **sh, t_token *tkn)
{
	t_rdr	*rdr;
	int		count;
	int		flag;

	(void)sh;
	count = 0;
	rdr = NULL;
	while (tkn && tkn->type != '|')
	{
		flag = 0;
		if (tkn->type == '<' || tkn->type == '>')
		{
			if (tkn->next->type == 'N' || !*(tkn->next->token))
				flag = 1;
			ft_rdr_addb(&rdr, ft_rdr_new(tkn->next->token, tkn->token, flag));
			count++;
		}
		tkn = tkn->next;
	}
	return (rdr);
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
	t_rdr	*rdr;

	printf("\tbef\n");
	while (tkn)
	{
	printf("\tin\n");
		rdr = add_in(&sh, tkn);
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
			if ((!tkn || tkn->type == '|'))
			{
				if (!cmd[0])
					ft_sh_addb(&sh, ft_sh_new(rdr, NULL, "CMD"));
				else
					ft_sh_addb(&sh, ft_sh_new(rdr, cmd, "CMD"));
			}
		}
		if (tkn && tkn->type == '|')
			ft_sh_addb(&sh, ft_sh_new(NULL, &tkn->token, "PIPE"));
		if (tkn)
			tkn = tkn->next;
	}
	return (sh);
}
