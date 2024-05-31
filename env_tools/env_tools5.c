/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:09:33 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 11:22:44 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_norm_env_add(t_env **head, int mode)
{
	if (!mode)
	{
		ft_env_addb(head,
			ft_env_lstnew("PWD", getcwd(NULL, MAXPATHLEN), 1));
		ft_env_addb(head,
			ft_env_lstnew("SHLVL", "1", 1));
		ft_env_addb(head,
			ft_env_lstnew("_", "/usr/bin/env", 1));
		ft_env_addb(head,
			ft_env_lstnew("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0));
	}
	else
	{
		ft_env_addb(head,
			ft_env_lstnew("OLDPWD", NULL, 1));
		ft_env_addb(head,
			ft_env_lstnew("PWD", getcwd(NULL, MAXPATHLEN), 1));
		ft_env_addb(head,
			ft_env_lstnew("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0));
		ft_env_addb(head, ft_env_lstnew("SHLVL", "1", 1));
	}
}

void	ft_norm_env_pre_add(t_env **head, int flg)
{
	if (!flg)
		ft_norm_env_add(head, 0);
	else
		ft_norm_env_add(head, 1);
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
