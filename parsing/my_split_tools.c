/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thedon <thedon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:54:29 by thedon            #+#    #+#             */
/*   Updated: 2024/04/06 00:05:38 by thedon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_word(char const **s, char c)
{
	if (**s == '\'' || **s == '"')
	{
		c = **s;
		(*s)++;
		while (**s && **s != c)
			(*s)++;
		(*s)++;
	}
	else
		while (**s && **s != c && **s != 9)
			(*s)++;
}

int	word_len(char const *str, char *c)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		*c = str[i];
		i++;
		while (str[i] && str[i] != *c)
			i++;
        if (str[i] && str[i] == *c)
            i++;
	}
	else
		while (str[i] && (str[i] != *c && str[i] != 9))
			i++;
	return (i);
}