/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:13:39 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/30 19:21:38 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_lg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_pp_join(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = ft_malloc(((ft_lg(s1) + ft_lg(s2) + ft_lg(s3)) * 1) + 1, 0);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	j = 0;
	while (s3[j])
		res[i++] = s3[j++];
	res[i] = '\0';
	return (res);
}

void	ft_perror(char *message)
{
	perror(message);
	exit(1);
}

void	ft_norm_close(int (*pp_chain)[2], int fd)
{
	close(pp_chain[fd][0]);
	close(pp_chain[fd][1]);
}

void	ft_norm_sclose(int (*pp_chain)[2], int fd)
{
	ft_norm_close(pp_chain, fd);
	ft_norm_close(pp_chain, fd - 1);
}
