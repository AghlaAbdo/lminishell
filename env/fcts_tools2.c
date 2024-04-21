/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:46:01 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/05 03:39:39 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	ft_len(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_tlen(char *s[])
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*tp;
	size_t	lenx;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	lenx = ft_len(s1);
	tp = (char *) ft_malloc(lenx + 1, 0);
	if (!tp)
		return (NULL);
	while (s1[i])
	{
		*(tp + i) = *(s1 + i);
		i++;
	}
	tp[i] = '\0';
	return (tp);
}

//! ftm (added m means that the function is modified from the original !!)
char	*ftm_sjoin(char *s1, char *s2)
{
	char	*j_s;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	j_s = (char *)ft_malloc(((ft_len(s1) + ft_len(s2) + 2) * sizeof(char)), 0);
	if (!j_s)
		return (NULL);
	while (s1[i])
	{
		j_s[i] = s1[i];
		i++;
	}
	j_s[i++] = '=';
	while (s2[j])
		j_s[i++] = s2[j++];
	j_s[i] = '\0';
	return (j_s);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == ft_len(s1) && ft_len(s1) == ft_len(s2))
		return (0);
	return (-1);
}
