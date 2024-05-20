/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 06:33:02 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/20 14:35:23 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*ft_token_new(char *word, char type, int len)
{
	t_token	*new;

	(void)len;
	new = ft_malloc(sizeof(t_token), 0);
	if (!new)
		return (NULL);
	new->token = word;
	new->type = type;
	// new->lst_len = len;
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

void	ft_token_rmv(t_token **head)
{
	t_token	*prev;
	t_token	*next;

	if (!head || !*head)
		return ;
	prev = (*head)->prev;
	next = (*head)->next;
	if (next)
	{
		*head = next;
		next->prev = prev;
		if (prev)
			prev->next = next;
	}
	else
		*head = NULL;
}
