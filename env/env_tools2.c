/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:52:29 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/05 03:39:31 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_env_new(t_env **env, char *key, char *value)
{
	t_env	*head;

	if (!*env || !key || !value)
		return ;
	head = *env;
	ft_env_addb(&head, ft_env_lstnew(ft_sdup(key), ft_sdup(value)));
}

void	ft_env_rmv(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	if (*head == NULL)
		return ;
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (prev == NULL)
		*head = current->next;
	else
		prev->next = current->next;
}

void	ft_env_dstry(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (env == NULL || *env == NULL)
		return ;
	current = *env;
	while (current != NULL)
	{
		next = current->next;
		current = next;
	}
	*env = NULL;
}

void	ft_env_prnt(t_env **env)
{
	t_env	*head;

	if (!*env || !env)
		return ;
	head = *env;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
