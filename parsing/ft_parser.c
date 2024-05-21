/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:54:38 by thedon            #+#    #+#             */
/*   Updated: 2024/05/21 19:42:32 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clean_exit(void)
{
	ft_malloc(0, 1);
	printf("\n\t-------------------------------------------------\n");
	// system("leaks minishell");
	// sleep(3);
	exit(0);
}

int	is_quote_closed(char *input)
{
	char	c;
	int	i;

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
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_syntax(t_token *tkn)
{
	if (*tkn->token == '|')
	{
		printf("lminishell: syntax error near unexpected token\n");
		return (1);
	}
	while (tkn)
	{
		if (!tkn->type
			|| (tkn->next && *tkn->next->token == '|' && (*tkn->token == '>'
			|| *tkn->token == '<' || *tkn->token == '|'))
			|| ((tkn->type == '>' || tkn->type == '<') && (!tkn->next || (tkn->next
			&& (tkn->next->type == '<' || tkn->next->type == '>')))))
		{
			printf("lminishell: syntax error near unexpected token\n");
			return (1);
		}
		if (!tkn->next)
			break ;
		tkn = tkn->next;
	}
	return (0);
}

// Used just to print result, will be deleted
void	print_tkn_exp(t_token *tkn, int i)
{
	if (i == 0)
	{
		printf("\n\t----Tokens result before expanding-----\n");
		while (tkn)
		{
			printf("\ttoken: [%s]\ttype: %c%%\n", tkn->token, tkn->type);
			tkn = tkn->next;
		}
		printf("\n\t---------------------------------------\n\n");
	}
	else
	{
		printf("\n\t----- Tokens result after expanding -----\n");
		while (tkn)
		{
			printf("\ttoken: [%s]\ttype: %c%%\n", tkn->token, tkn->type);
			tkn = tkn->next;
		}
		printf("\n\t-----------------------------------------\n\n");
	}
	
}

// Used just to print result, will be deleted
void	print_sh_token(t_sh *res, char *line, char *here, int fd)
{	
	int		i;
	
	(void)line;
	(void)here;
	(void)fd;
	t_rdr	*rdr_head;//!by_sala7

	rdr_head = res->rdr;//!by_sala7 hint kenti kat incremente l head  o kiwsalni NULL 
	printf("\n\t-------- SH Token result --------\n\n");
	while (res)
	{
		if (res->rdr)
			prnt_rdr(res->rdr);
		// {
		// 	while (rdr_head)
		// 	{
		// 		if (!ft_strcmp(rdr_head->mode, "<<"))
		// 		{
		// 			fd = open(rdr_head->fl_name, O_RDONLY);
		// 			// here = "";
		// 			// line = get_next_line(fd);
		// 			// while (line)
		// 			// {
		// 			// 	here = ft_pstrjoin(here, line);
		// 			// 	free(line);
		// 			// 	line = get_next_line(fd);
		// 			// }
		// 			printf("fl_name: [%s]\tmode: [%s]\tcontent: [in file]\n", rdr_head->fl_name, rdr_head->mode);
					
		// 		}
		// 		else
		// 			printf("fl_name: [%s]\tmode: [%s]\n", rdr_head->fl_name, rdr_head->mode);
		// 		rdr_head = rdr_head->next;
		// 	}
		// }
		if (res->value)
		{
			if (!ft_strcmp(res->type, "CMD"))
			{
				i = 0;
				printf("value = [%s]\t| type = [%s]\n", res->value[i++], res->type);
				while (res->value[i])
					printf("\tvalue = [%s]\n", res->value[i++]);
				printf("\n");
			}
			else
			{
				printf("value = [%s]\t| type = [%s]\n", res->value[0], res->type);
				if (!ft_strcmp(res->type, "PIPE"))
					printf("\n");
			}
			
		}
		res = res->next;
	}
	printf("\n\t-------------------------------\n\n");
	
}

t_sh	*ft_parser(char *input, t_parms *prms)
{
	t_sh	*res;
	t_token	*tkn;

	if (!*input || is_quote_closed(input))
		return (NULL);
	input = ft_strtrim(input, " \t");
	if (!input || !*input)
		return (NULL);
	tkn = parse_input(NULL, input, NULL, 0);
	if (check_syntax(tkn))
		return (NULL);
	// print_tkn_exp(tkn, 0);
	ft_expand(tkn, prms);
	here_doc(tkn, prms);
	// rmv_quotes(tkn);
	// print_tkn_exp(tkn, 1);
	res = ft_tokenization(NULL, tkn, NULL, 0);
	if (!ft_strcmp(input, "exit"))
		clean_exit();
	// printf("size is: [%d]\n", ft_sh_sz(&res));
	print_sh_token(res, NULL, NULL, 0);
	return (res);
}
