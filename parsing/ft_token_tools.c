/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 06:33:02 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/30 22:03:37 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*ft_token_new(char *word, char type)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 0);
	if (!new)
		return (NULL);
	new->token = word;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_token_addb(t_token **head, t_token *new)
{
	t_token	*current;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		new->next = NULL;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	new->next = NULL;
}

void	ft_token_insrt(t_token **head, t_token *new)
{
	t_token	*next;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		new->next = NULL;
		return ;
	}
	next = (*head)->next;
	if (next)
		next->prev = new;
	(*head)->next = new;
	new->next = next;
	new->prev = *head;
}

void	ft_token_rmv(t_token **head, t_token *rmv)
{
	t_token	*prev;
	t_token	*next;
	t_token	*curr;

	if (!head || !*head || !rmv)
		return ;
	if (*head == rmv)
	{
		prev = (*head)->prev;
		next = (*head)->next;
		*head = next;
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		return ;
	}
	curr = *head;
	while (curr && curr != rmv)
		curr = curr->next;
	if (curr == rmv)
	{
		prev = curr->prev;
		next = curr->next;
		if (next)
		{
			curr = next;
			next->prev = prev;
			if (prev)
				prev->next = next;
		}
		else if (prev)
		{
			curr = next;
			prev->next = curr;
		}
	}
}
