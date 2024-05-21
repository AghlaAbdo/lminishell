/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:55:01 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/17 19:46:07 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"


void ft_env_insrt(t_env **head, char *key, char *value)
{
	t_env	*n_node;
	t_env *current;
	t_env *prev;

	n_node = ft_env_lstnew(key, value, 1);
	current = *head;
	prev = NULL;
	if (!n_node)
		return;
	while (current != NULL && ft_insrt_strcmp(key, current->key) > 0)
	{
		prev = current;
		current = current->next;
	}
	if (prev == NULL)
	{
		n_node->next = *head;
		*head = n_node;
	}
	else
	{
		prev->next = n_node;
		n_node->next = current;
	}
}

int	ft_env_exists(t_env	**env, char *key)
{
	t_env	*head;

	if (!env || !(*env))
		return (0);
	head = *env;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
				return (1);
		head = head->next;
	}
	return (0);
}
