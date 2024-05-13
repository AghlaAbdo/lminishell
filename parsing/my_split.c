/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:53:36 by thedon            #+#    #+#             */
/*   Updated: 2024/05/13 18:42:15 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == 9))
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c && s[i] != 9)
			i++;
	}
	return (count);
}

static char	*word(char const *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != 9)
		i++;
	word = ft_malloc((i +1) * sizeof(char), 0);
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c && str[i] != 9)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**freearr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

char	**my_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)ft_malloc((wordcount(s, c) + 1) * sizeof(char *), 0);
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c || *s == 9))
			s++;
		if (*s)
		{
			arr[i] = word(s, c);
			if (!arr[i])
				return (freearr(arr, i));
			i++;
		}
		while (*s && *s != c && *s != 9)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}