/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:00:38 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/17 15:57:53 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free_it(char *s)
{
	free(s);
	return (NULL);
}

int	ft_strlen(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != (char)c)
		i++;
	return (i);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (*s == (char)c)
// 		return ((char *)s);
// 	return (NULL);
// }

char	*gt_strjoin(char *s1, char *s2, int rd)
{
	char	*str;
	int		i;

	if (!s1)
		s1 = "\0";
	i = ft_strlen(s1, 0);
	str = (char *)malloc((i + rd +1) * sizeof(char));
	if (!str)
	{
		if (s1[0])
			free(s1);
		return (NULL);
	}
	i = 0;
	rd = 0;
	while (s1[i])
		str[rd++] = s1[i++];
	i = 0;
	while (s2[i])
		str[rd++] = s2[i++];
	str[rd] = '\0';
	if (s1[0])
		free(s1);
	return (str);
}
