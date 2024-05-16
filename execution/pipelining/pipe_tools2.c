/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:48:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/04 09:10:33 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_sprtor(char c)
{
	return (c == ' ' || c == '\t' || c == ':');
}

char	*ft_pp_strncpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_pp_wrd_cnt(char *s)
{
	int	i;
	int	nb_wd;

	i = 0;
	nb_wd = 0;
	while (s[i])
	{
		while (s[i] && ft_sprtor(s[i]))
			i++;
		if (s[i] && !ft_sprtor(s[i]))
		{
			nb_wd++;
			i++;
		}
		while (s[i] && !ft_sprtor(s[i]))
			i++;
	}
	return (nb_wd);
}

char	*ft_pp_allocopy(char *s)
{
	int		i;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && !ft_sprtor(s[i]))
		i++;
	word = ft_malloc(i + 1, 0);
	if (!word)
		return (NULL);
	word = ft_pp_strncpy(word, s, i);
	return (word);
}

char	**ft_pp_split(char *str, int flag)
{
	int		i;
	int		j;
	char	**res;

	j = 0;
	i = 0;
	res = ft_malloc(sizeof(char *) * (ft_pp_wrd_cnt(str) + 1), 0);
	if (!res)
		return (NULL);
	while (str[i] && j < ft_pp_wrd_cnt(str))
	{
		while (str[i] && ft_sprtor(str[i]))
			i++;
		if (str[i] && !ft_sprtor(str[i]))
		{
			res[j] = ft_pp_allocopy(&str[i]);
			if (!res[j++])
				return (NULL);
		}
		while (str[i] && !ft_sprtor(str[i]))
			i++;
	}
	if (flag == 1)
		free(str);
	return (res[j] = NULL, res);
}
