/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:18:50 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/16 18:07:10 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	**ft_env_to_dp(t_env **env)
{
	char	**res;
	t_env	*head;
	int		i;

	if (!env || !(*env))
		return (0);
	i = 0;
	if (!env || !*env)
		return (NULL);
	head = *env;
	res = ft_malloc((sizeof(char *)) * (ft_env_sz(env) + 1), 0);
	while (head && i < ft_env_sz(env))
	{
		res[i++] = ftm_sjoin(head->key, head->value);
		head = head->next;
	}
	res[i] = NULL;
	return (res);
}

void	ft_env_updt(t_env **env, char *key, char *nw_vl)
{
	t_env	*head;
	char	*new;

	if (!env || !(*env))
		return ;
	head = *env;
	new = ft_sdup(nw_vl);
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
		{
			head->value = new;
			return ;
		}
		head = head->next;
	}
}

// t_env	*ft_env_dup(t_env	**env)
// {
// 	t_env	*head;
// 	t_env	*res;

// 	if (!env || !(*env))
// 		return (0);
// 	head = *env;
// 	res = ft_env_crt(ft_env_to_dp(env));
// 	// if (!res)
// 	// {
// 	// 	ft_env_addb(&res, ft_env_lstnew("OLDPWD", NULL));
// 	// 	ft_env_addb(&res, ft_env_lstnew("aSDFGHNJ", getcwd(NULL, MAXPATHLEN)));
// 	// 	ft_env_addb(&res, ft_env_lstnew("SHLVL", "1"));
// 	// }
// 	return (res);
// }

void	ft_swap(t_env *n1, t_env *n2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = n1->key;
	tmp_value = n1->value;
	n1->key = n2->key;
	n1->value = n2->value;
	n2->key = tmp_key;
	n2->value = tmp_value;
}

t_env	*ft_env_sort(t_env **env)
{
	t_env	*head;
	t_env	*c_node;
	t_env	*n_node;

	if (!env || !(*env))
		return (0);
	head = *env;
	c_node = head;
	while (c_node)
	{
		n_node = c_node->next;
		while (n_node)
		{
			if (ft_strcmp(c_node->key, n_node->key) > 0)
				ft_swap(c_node, n_node);
			n_node = n_node->next;
		}
		c_node = c_node->next;
	}
	return (head);
}
