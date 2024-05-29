/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:56:58 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/06 10:02:28 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*ft_strncpy(char *dst, char *src, size_t len)
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

int	ft_wrd_cnt(char *s, char sep)
{
	int	i;
	int	nb_wd;

	i = 0;
	nb_wd = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i] && s[i] != sep)
		{
			nb_wd++;
			i++;
		}
		while (s[i] && s[i] != sep)
			i++;
	}
	return (nb_wd);
}

char	*ft_allocopy(char *s, char sep)
{
	int		i;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != sep)
		i++;
	word = ft_malloc(i + 1, 0);
	if (!word)
		return (NULL);
	word = ft_strncpy(word, s, i);
	return (word);
}

char	**ft_splt(char *str, char sep)
{
	int		i;
	int		j;
	char	**res;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	res = ft_malloc(sizeof(char *) * (ft_wrd_cnt(str, sep) + 1), 0);
	if (!res)
		return (NULL);
	while (str[i] && j < ft_wrd_cnt(str, sep))
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
		{
			res[j] = ft_allocopy(&str[i], sep);
			if (!res[j++])
				return (NULL);
		}
		while (str[i] && str[i] != sep)
			i++;
	}
	return (res[j] = NULL, res);
}
