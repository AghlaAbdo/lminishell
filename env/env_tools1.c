/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:52:07 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/23 14:57:04 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_env_addb(t_env **lst, t_env *newn)
{
	t_env	*current;

	if (!lst || !newn)
		return ;
	if (*lst == NULL)
	{
		*lst = newn;
		newn->next = NULL;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = newn;
	newn->next = NULL;
}

t_env	*ft_env_lstnew(void *key, void *value)
{
	t_env	*new_node;

	new_node = ft_malloc(sizeof(t_env), 0);
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

char	*ft_env_eqls(char *res[])
{
	int		i;
	char	*out;
	char	*tmp;

	i = 0;
	out = NULL;
	while (res[++i])
	{
		tmp = res[i];
		if (out == NULL)
			out = ftm_sjoin(res[i], res[i + 1]);
		else
			out = ftm_sjoin(out, res[i]);
	}
	return (out);
}

t_env	*ft_env_crt(char *ep[])
{
	int		i;
	int		j;
	char	**res;
	t_env	*head;

	i = -1;
	j = 2;
	head = NULL;
	while (ep[++i])
	{
		res = ft_splt(ep[i], '=');
		if (ft_tlen(res) == 2)
			ft_env_addb(&head, ft_env_lstnew(res[0], res[1]));
		else if (ft_tlen(res) > 2)
		{
			ft_env_addb(&head, ft_env_lstnew(res[0], ft_env_eqls(res)));
		}
	}
	return (head);
}

char	*ft_env_srch(char	*key, t_env	**env)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			if (head->value != NULL)
				return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}
