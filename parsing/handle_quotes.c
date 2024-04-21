/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:11:51 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/21 19:59:34 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_char(char *str, char c)
{
    int len;
	int	i;
	int	j;

    len = ft_len(str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != c)
			str[j++] = str[i];
		i++;
	}
    str[j] = '\0';
}

//	Check if the previous opened quote is closed
int	check_prev_closed(char *input, char *c)
{
	char	opos;
	int		i;
	int		count;

	if (*c == '"')
		opos = '\'';
	else
		opos = '"';
	i = -1;
	count = 0;
	while (input[++i] && input[i] != opos)
		if (input[i] == *c)
			count++;
	if (!count)
		return (0);
	return (count % 2);
}

//	Count the number of quotes and see if every opened quote is closed
int	count_quotes(char *input, char *c)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (input[++i])
		if (input[i] == *c)
			count++;
	while (i-- >= 0)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (input[i] == *c)
				break ;
			else if (check_prev_closed(input, c))
			{
				*c = input[i];
				return (!count_quotes(input, c));
			}
		}
	}
	if (!count)
		return (0);
	return (count % 2);
}

//	Keep reading untill every opened quote is closed
char	*keep_reading(t_histr **histr, char *input, char *c, int i)
{
	char	*line;

	input = ft_strjoin(input, "\n");
	while (1)
	{
		while (input[i])
			i++;
		line = readline("> ");
		if (!line)
		{
			printf("minishell: unexpected EOF while looking for matching `%c`\n", *c);
			printf("minishell: syntax error: unexpected end of file\n");
			clean_exit();
		}
		input = ft_strjoin(input, line);
		rl_clear_history();
		ft_hist_rmvlast(histr);
		ft_hist_addb(histr, ft_hist_new(my_strdup(input)));
		ft_add_histr(histr);
		add_history(input);
		if (count_quotes(input + i, c))
			return (free(line), ft_strtrim(input, "\n"));
		free(line);
		input = ft_strjoin(input, "\n");
	}
}


char	*handle_quotes(t_histr **histr, char *input)
{
	char	*line;
	char	c;
	int		i;

	i = 0;
	ft_hist_addb(histr, ft_hist_new(my_strdup(input)));
	add_history(input);
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i];
			while (input[++i] && input[i] != c)
				;
			if (input[i] != c)
				return (keep_reading(histr, input, &c, i));
		}
		i++;
	}
	return (input);
}
