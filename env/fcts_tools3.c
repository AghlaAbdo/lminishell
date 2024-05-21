/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:43:14 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/16 18:08:41 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*ft_sdup(char *s1)
{
	char	*tp;
	size_t	lenx;
	size_t	i;

	if (!s1)
		return (0);
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

int	ft_env_sz(t_env	**env)
{
	int		i;
	t_env	*head;

	if (!env)
		return (-1);
	i = 0;
	head = *env;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}
