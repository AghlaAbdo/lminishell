/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:54:38 by thedon            #+#    #+#             */
/*   Updated: 2024/05/09 20:12:23 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Check the variable is inside which quotes
char	*check_quotes(char *prompt)
{
	if (*prompt == '\'' || *prompt == '"')
		return ("STR");
	else
		return ("VAR");
}

void	clean_exit(void)
{
	ft_malloc(0, 1);
	printf("\n\t-------------------------------------------------\n");
	system("leaks minishell");
	// sleep(3);
	exit(0);
}

// As the name suggest
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

int	special_chars(t_token *tkn)
{
	if (*tkn->token == '|')
	{
		printf("lminishell: syntax error near unexpected token\n");
		return (1);
	}
	while (tkn)
	{
		if (!tkn->type
			|| tkn->next && *tkn->next->token == '|' && (*tkn->token == '>'
			|| *tkn->token == '<' || *tkn->token == '|'))
		{
			printf("lminishell: syntax error near unexpected token\n");
			return (1);
		}
		if (!tkn->next)
			break ;
		tkn = tkn->next;
	}
	if (*tkn->token == '|' || *tkn->token == '>' || *tkn->token == '<'
		|| (tkn->prev && (*tkn->prev->token == '|' || *tkn->prev->token == '>' || *tkn->prev->token == '<')
		&& (!ft_strcmp(tkn->token, "\"\"")
			|| !ft_strcmp(tkn->token, "''"))))
	{
			printf("lminishell: syntax error near unexpected token\n");
			return (1);
	}
	return (0);
}

int	check_syntax(t_token *tkn, t_parms *prms)
{
	if (special_chars(tkn))
		return (1);
	
	
	return (0);
}

t_sh	*ft_parser(char *input, t_parms *prms)
{
	t_sh	*res;
	t_token	*tkn;
	char	**prompt;
	int		i;
	char	*value;

	// input = handle_quotes(&prms->histr, input);
	if (!*input || is_quote_closed(input))
		return (NULL);
	input = ft_strtrim(input, " \t");
	// prompt = my_split(input, ' ');
	// for(int i = 0; prompt[i]; i++)
	// 	printf("[%d]: %s\n", i, prompt[i]);
	tkn = parse_input(NULL, input, NULL, 0);
	if (check_syntax(tkn, prms))
		return (NULL);
	t_token	*temp = tkn;
	printf("\n\t----Tokens result before expanding-----\n");
	while (temp)
	{
		printf("\ttoken: [%s]\ttype: %c%%\n", temp->token, temp->type);
		temp = temp->next;
	}
	printf("\n\t----------------\n\n");
	temp = tkn;
	ft_expand(&tkn, prms);
	printf("out of expnding\n");
	here_doc(tkn, prms);
	rmv_quotes(tkn);
	printf("\n\t----Tokens result-----\n");
	while (temp)
	{
		printf("\ttoken: [%s]\ttype: %c%%\n", temp->token, temp->type);
		temp = temp->next;
	}
	printf("\n\t----------------\n\n");
	res = ft_tokenization(tkn);
	printf("here after?\n");
	i = -1;
	// res = NULL;
	// while (prompt[++i])
	// {
		if (!ft_strcmp(input, "exit"))
			clean_exit();
		// if (ft_strchr(prompt[i], '$'))
		// {
		// 	value = ft_expand(prompt[i], prms);
		// 	ft_sh_addb(&res, ft_sh_new(&value, check_quotes(prompt[i])));
		// }
		// else if (!ft_strcmp(prompt[i], "<") || !ft_strcmp(prompt[i], ">"))
		// {
		// 	ft_sh_addb(&res, ft_sh_new(&prompt[i], "REDIR"));
		// 	// ft_sh_addb(&res, ft_sh_new(&prompt[i], "FILE"));
		// }
		// else if (!ft_strcmp(prompt[i], "|"))
		// {
		// 	ft_sh_addb(&res, ft_sh_new(&prompt[i], "PIPE"));
		// }
		// else
		// 	printf("[%s] NONE of the above types\n", prompt[i]);
	// }
	printf("\n\t-------- SH Token result --------\n\n");
	// for (int i = 0; res->value[i]; i++)
	// 	printf("res: [%s]\n", res->value[i]);
	while (res)
	{
		if (!res->value)
		{
			while (res->rdr)
			{
				printf("fl_name: [%s]\tmode: [%s]\n", res->rdr->fl_name, res->rdr->mode);
				res->rdr = res->rdr->next;
			}
		}
		else
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
	return (res);
}
