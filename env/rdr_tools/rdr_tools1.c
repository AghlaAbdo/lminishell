/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:28:31 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/20 15:59:53 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/minishell.h"

t_rdr	*ft_rdr_new(char *fl_name, char *mode, int flag)
{
	t_rdr	*new_node;

	new_node = ft_malloc(sizeof(t_rdr), 0);
	if (!new_node)
		return (NULL);
	new_node->fl_name = fl_name;
	new_node->mode = mode;
	new_node->flag = flag;
	new_node->next = NULL;
	return (new_node);
}

void	ft_rdr_addb(t_rdr **rdr, t_rdr *n_node)
{
	t_rdr	*current;

	if (!rdr || !n_node)
		return ;
	if (*rdr == NULL)
	{
		*rdr = n_node;
		n_node->next = NULL;
		return ;
	}
	current = *rdr;
	while (current->next != NULL)
		current = current->next;
	current->next = n_node;
	n_node->next = NULL;
}

