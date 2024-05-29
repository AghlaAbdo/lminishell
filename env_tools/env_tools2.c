/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:52:29 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/16 18:05:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"
#include <stdio.h>

void	ft_env_new(t_env **env, char *key, char *value)
{
	t_env	*head;

	if (!(*env) || !key || !value || !env)
		return ;
	head = *env;
	ft_env_addb(&head, ft_env_lstnew(ft_sdup(key), ft_sdup(value), 1));
}

void	ft_env_rmv(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!head || !(*head))
		return ;
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

	if (!env || !(*env))
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

	if (!(*env) || !env)
		return ;
	head = *env;
	while (head)
	{
		if (head->visible != 0)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

int	ft_only_quotes(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] != '"' && s[i] != '\'')
			return (0);
	}
	return (1);
}

void	ft_env_prnt_fexprt(t_env **env)
{
	t_env	*head;

	if (!(*env) || !env)
		return ;
	head = *env;
	while (head)
	{
		if (head->visible == 1)
		{
			if (head->value == NULL || (ft_len(head->value) == 0 && ft_strcmp(head->key, "OLDPWD") == 0))
				printf("declare -x %s\n", head->key);
			else if (head->value != NULL && ft_only_quotes(head->value) && ft_len(head->value) == 2)
				printf("declare -x %s=%s\n", head->key, head->value);
			else if (head->value != NULL && ft_len(head->value) == 0)
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
			else
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
		}
		head = head->next;

	}
}
