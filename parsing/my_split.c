/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:53:36 by thedon            #+#    #+#             */
/*   Updated: 2024/04/17 16:02:56 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	wordcount(char const *s, char c)
{
	int		i;
	int		count;
	char	first_c;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == 9))
			i++;
		if (s[i] == '\'' || s[i] == '"')
		{
			first_c = s[i++];
			while (s[i] && s[i] != first_c)
				i++;
		}
		// printf("i in the middle = %d\n", i);
		if (s[i])
			count++;
		while (s[i] && s[i] != c && s[i] != 9)
		{
			// printf("s[%d] = |%c|\n", i, s[i]);
			i++;
		}
	}
	// printf("word count in split = %d| and c = |%c| and str = %s|\n", count, c, s);
	return (count);
}

static char	*word(char const *str, char c)
{
	char	*word;
	int		i;
	int		j;

	i = word_len(str, &c);
	word = ft_malloc((i +1) * sizeof(char), 0);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	if (c == '\'' || c == '"')
	{
        word[j++] = str[i++];
		while (str[i] && str[i] != c)
			word[j++] = str[i++];
        word[j++] = str[i++];
	}
	else
		while (str[i] && str[i] != c && str[i] != 9)
			word[j++] = str[i++];
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
		skip_word(&s, c);
	}
	arr[i] = NULL;
	return (arr);
}