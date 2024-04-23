/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histr_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:21:08 by aaghla            #+#    #+#             */
/*   Updated: 2024/04/22 16:05:53 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_histr	*ft_hist_new(char *line)
{
	t_histr	*new;

	new = ft_malloc(sizeof(t_histr), 0);
	if (!new)
		return (NULL);
	new->line = line;
	new->next= NULL;
	return (new);
}
void	ft_hist_addb(t_histr **histr, t_histr *new)
{
	t_histr	*current;
	
	if (!histr || !new)
		return ;
	if (!*histr)
	{
		*histr = new;
		new->next = NULL;
		return ;
	}
	current = *histr;
	while (current->next)
		current = current->next;
	current->next = new;
	new->next = NULL;
}

void	ft_hist_rmvlast(t_histr **histr)
{
	t_histr	*current;
	t_histr	*temp;

	if (!histr || !*histr)
		return ;
	temp = *histr;
	current = *histr;
	if (!current->next)
	{
		*histr = NULL;
		return ;
	}
	while (current->next->next)
		current = current->next;
	current->next = NULL;
}

void	ft_add_histr(t_histr **histr)
{
	t_histr	*head;

	if (!histr || !*histr)
		return ;
	head = *histr;
	while (head->next)
	{
		add_history(head->line);
		head = head->next;
	}
}
