/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tools1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:32:49 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/09 20:05:40 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_sh_sz(t_sh **sh)
{
	int		i;
	t_sh	*head;

	if (!sh)
		return (-1);
	head = *sh;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

t_sh	*ft_sh_new(t_rdr *rdr, char **value, char *type)//!y9adro yezado members so aydar hadchi fstruct
{
	t_sh	*new_node;

	new_node = ft_malloc(sizeof(t_sh), 0);
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->rdr = rdr;
	new_node->next = NULL;
	return (new_node);
}

void	ft_sh_addb(t_sh **sh, t_sh *new_sh)
{
	t_sh	*current;

	if (!sh || !new_sh)
		return ;
	if (*sh == NULL)
	{
		*sh = new_sh;
		new_sh->next = NULL;
		return ;
	}
	current = *sh;
	while (current->next != NULL)
		current = current->next;
	current->next = new_sh;
	new_sh->next = NULL;
}

void	ft_sh_rmv(t_sh **sh, char *value)
{
	t_sh	*current;
	t_sh	*prev;

	current = *sh;
	prev = NULL;
	if (*sh == NULL)
		return ;
	while (current != NULL && ft_strcmp(*current->value, value) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (prev == NULL)
		*sh = current->next;
	else
		prev->next = current->next;
}