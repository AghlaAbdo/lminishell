/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:52:07 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/24 21:20:08 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"
#include <stdio.h>

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

t_env	*ft_env_lstnew(void *key, void *value, int vsbl)
{
	t_env	*new_node;

	if (!key)
		return (0);
	new_node = ft_malloc(sizeof(t_env), 0);
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->visible = vsbl;
	new_node->next = NULL;
	return (new_node);
}

char	*ft_env_eqls(char *res[])
{
	int		i;
	char	*out;
	char	*tmp;

	if (!res || !(*res))
		return (0);
	i = 0;
	out = NULL;
	while (res[++i])
	{
		tmp = res[i];
		if (out == NULL)
		{
			out = ftm_sjoin(res[i], res[i + 1]);
			i++;
		}
		else
			out = ftm_sjoin(out, res[i]);
	}
	return (out);
}

t_env	*ft_env_crt(char *ep[], int flg)
{
	int		i;
	int		j;
	t_env	*head = NULL;
	char	**res;

	if (!(*ep))
	{
		if (!flg)
		{
			ft_env_addb(&head, ft_env_lstnew("PWD", getcwd(NULL, MAXPATHLEN), 1));
			ft_env_addb(&head, ft_env_lstnew("SHLVL", "1", 1));
			ft_env_addb(&head, ft_env_lstnew("_", "/usr/bin/env", 1));
			ft_env_addb(&head, ft_env_lstnew("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0));
		}
		else
		{
			ft_env_addb(&head, ft_env_lstnew("OLDPWD", NULL, 1));
			ft_env_addb(&head, ft_env_lstnew("PWD", getcwd(NULL, MAXPATHLEN), 1));
			ft_env_addb(&head, ft_env_lstnew("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0));
			ft_env_addb(&head, ft_env_lstnew("SHLVL", "1", 1));
		}
		return (head);
	}
	i = -1;
	j = 2;
	head = NULL;
	while (ep[++i])
	{
		res = ft_splt(ep[i], '=');
		
		if (ft_tlen(res) == 2)
			ft_env_addb(&head, ft_env_lstnew(res[0], res[1], 1));
		else if (ft_tlen(res) == 1)
			ft_env_addb(&head, ft_env_lstnew(res[0], "", 1));
		else if (ft_tlen(res) > 2)
			ft_env_addb(&head, ft_env_lstnew(res[0], ft_env_eqls(res), 1));
	}
	return (head);
}

char	*ft_env_srch(char	*key, t_env	**env)
{
	t_env	*head;

	if (!env || !(*env))
		return (0);
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
