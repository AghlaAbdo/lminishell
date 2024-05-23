/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:08:34 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/23 15:01:18 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_var	*ft_var_new(char *wrd, char type, int is_f)
{
	t_var	*new;

	new = ft_malloc(sizeof(t_var), 0);
	if (!new)
		return (NULL);
	new->wrd = wrd;
	new->type = type;
	new->is_f = is_f;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_var_addb(t_var **head, t_var *new)
{
	t_var	*current;

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

void	ft_var_insrt(t_var **head, t_var *new)
{
	t_var	*next;

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
