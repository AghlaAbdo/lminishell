/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:22:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/08 18:59:41 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	in_file(t_sh **sh, t_token *in, t_token *tkn)
{
	printf("called in_file?\n");
	while (in->next && in->type != '|')
	{
		printf("skipped [%s]\n", in->token);
		in = in->next;
	}
	// if (in)
	// 	in = in->prev;
	while (in && in != tkn->prev)
	{
		printf("back to [%s]\n", in->token);
		if (in->prev && in->prev->type == '<')
		{
			ft_sh_addb(sh, ft_sh_new(&in->prev->token, "REDIR"));
			if (!ft_strcmp(in->token, "<<"))
				ft_sh_addb(sh, ft_sh_new(&in->token, "HERE"));
			else
				ft_sh_addb(sh, ft_sh_new(&in->token, "FILE"));
			break;
		}
		in = in->prev;
	}
}

void	out_file(t_sh **sh, t_token *out, t_token *tkn)
{
	printf("called out_file\n");
	while (out->next && out->type != '|')
	{
		printf("skipped [%s]\n", out->token);
		out = out->next;
	}
	// if (out)
	// 	out = out->prev;
	while (out && out != tkn->prev)
	{
		printf("back to [%s]\n", out->token);
		if (out->prev && out->prev->type == '>')
		{
			ft_sh_addb(sh, ft_sh_new(&out->prev->token, "REDIR"));
			ft_sh_addb(sh, ft_sh_new(&out->token, "FILE"));
			break;
		}
		out = out->prev;
	}
}

t_sh	*ft_tokenization(t_token *tkn)
{
	t_sh	*sh;
	t_token	*in;
	t_token	*out;
	t_token	*temp;
	char	**cmd;
	int		count;
	int		i;

	sh = NULL;
	while (tkn)
	{
		in = tkn;
		out	 = tkn;
		in_file(&sh, in, tkn);
		out_file(&sh, in, tkn);
		count = 0;
		temp = tkn;
		while (temp && temp->type != '|')
		{
			printf("Added [%s]\n", temp->token);
			if (!temp->prev || (temp->prev && temp->prev->type != '<' && temp->prev->type != '>'
				&& temp->type != '<' && temp->type != '>'))
			{
				count++;
			}
			temp = temp->next;
		}
		printf("count = %d\n", count);
		cmd = (char **)ft_malloc((count +1) * sizeof(char *), 0);
		i = 0;
		while (tkn && tkn->type != '|')
		{
			printf("tkn skipped [%s]\n", tkn->token);
			if (!tkn->prev || (tkn->prev && tkn->prev->type != '<' && tkn->prev->type != '>'
				&& tkn->type != '<' && tkn->type != '>'))
			{
				cmd[i++] = tkn->token;
				printf("ever really added?\n");
			}
			tkn = tkn->next;
			if (!tkn || tkn->type == '|')
			{
				cmd[i] = NULL;
				ft_sh_addb(&sh, ft_sh_new(cmd, "CMD"));
			}
		}
		if (tkn && tkn->type == '|')
			ft_sh_addb(&sh, ft_sh_new(&tkn->token, "PIPE"));
		if (tkn)
			tkn = tkn->next;
	}
	return (sh);
}
