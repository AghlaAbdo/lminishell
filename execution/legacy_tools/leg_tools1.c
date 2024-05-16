/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leg_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:51:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/23 18:37:56 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*j_s;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_sdup(s2));
	if (!s2)
		return (ft_sdup(s1));
	i = 0;
	j = 0;
	j_s = ft_malloc(((ft_len(s1) + ft_len(s2) + 1) * sizeof(char)), 0);
	while (s1[i])
	{
		j_s[i] = s1[i];
		i++;
	}
	while (s2[j])
		j_s[i++] = s2[j++];
	j_s[i] = '\0';
	return (j_s);
}

void	ft_error(char *s)
{
	write(2, "exit : ", 8);
	write(2, s, ft_len(s));
	write(2, ": numeric argument required\n", 29);
	exit (255);
}

int is_whitespace(char c)
{
	return c == ' ' || (c >= '\t' && c <= '\r');
}

long long ft_ext_atoi(char *s)
{
	long long	res;
	int			sign;
	int			digit;
	size_t		i;

	if (!s)
		return 0;
	res = 0;
	sign = 1;
	i = 0;
	digit = 0;
	while (is_whitespace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		sign = (s[i] == '-') ? -1 : 1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		digit = s[i] - '0';
		if ((sign == 1 && res > (LONG_MAX - digit) / 10) ||
			(sign == -1 && res < (LONG_MIN + digit) / 10))
			ft_error(s);
		res = res * 10 + digit;
		i++;
	}
	return (res * sign);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*substring;
	int		i;

	if (!s)
		return (NULL);
	if (start > ft_len(s))
		return (ft_sdup(""));
	if (len > ft_len(s + start))
		len = ft_len(s + start);
	i = 0;
	substring = ft_malloc((len * sizeof(char)) + 1, 0);
	if (!substring)
		return (NULL);
	while (s[start] && i < len)
	{
		substring[i] = s[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
