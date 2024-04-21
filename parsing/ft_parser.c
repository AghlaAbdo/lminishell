/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:54:38 by thedon            #+#    #+#             */
/*   Updated: 2024/04/21 19:41:17 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	testing(void)
{
	int	i = 97;
	t_histr	*hist;
	
	hist = NULL;
	while (i <= 123)
	{
		ft_hist_addb(&hist, ft_hist_new(my_strdup(&i)));
		i++;
	}
	ft_hist_rmvlast(&hist);
	ft_hist_rmvlast(&hist);
	ft_hist_rmvlast(&hist);
	while (hist->next)
	{
		printf("%s|\n", hist->line);
		hist = hist->next;
	}
	printf("-------------------\n");
}

t_sh	*ft_parser(char *input, t_parms *prms)
{
	t_sh	*res;
	char	**prompt;
	int		i;
	char	**value;

	// testing();
	input = handle_quotes(&prms->histr, input);
	printf("\n\tiput after handling: %s|\n", input);
	prompt = my_split(input, ' ');
	printf("\n\t----split result-----\n");
	for(int i = 0; prompt[i]; i++)
		printf("[%d]: %s\n", i, prompt[i]);
	printf("\t----------------\n");
	i = -1;
	res = NULL;
	while (prompt[++i])
	{
		if (!ft_strcmp(prompt[i], "exit"))
			clean_exit();
		if (ft_strchr(prompt[i], '$'))
		{
			value = (char **)ft_malloc(sizeof(char *), 0);
			*value = ft_expand(prompt[i], prms);
			ft_sh_addb(&res, ft_sh_new(value, check_quotes(prompt[i])));
		}
		else if (!ft_strcmp(prompt[i], "<") || !ft_strcmp(prompt[i], ">"))
		{
			ft_sh_addb(&res, ft_sh_new(&prompt[i++], "REDIR"));
			ft_sh_addb(&res, ft_sh_new(&prompt[i], "FILE"));
		}
		else if (!ft_strcmp(prompt[i], "|"))
		{
			ft_sh_addb(&res, ft_sh_new(&prompt[i], "PIPE"));
		}
		else
			printf("[%s] NONE of the above types\n", prompt[i]);
	}
	while (res)
	{
		printf("type = %s\t| value = %s$\n", res->type, res->value[0]);
		res = res->next;
	}
	return (res);
}
