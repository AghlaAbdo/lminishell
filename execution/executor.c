/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:53:35 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/15 11:54:10 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>

int	ft_router(t_sh *sh, t_parms *param)
{
	t_sh	*head;
	int		ex_stts;

	head = sh;
	ex_stts = 0;
	if (head->value)
	{
		if (ft_strcmp(head->value[0], "env") == 0)
			ex_stts = ft_env(sh, param);
		else if (ft_strcmp(head->value[0], "pwd") == 0)
			ex_stts = ft_pwd(sh, param);
		else if (ft_strcmp(head->value[0], "echo") == 0)
			ex_stts = ft_echo(sh, param);
		else if (ft_strcmp(head->value[0], "cd") == 0)
			ex_stts = ft_cd(sh, param);
		else if (ft_strcmp(head->value[0], "exit") == 0)
			ft_exit(sh->value, param);
		else if (ft_strcmp(head->value[0], "export") == 0)
			ex_stts = ft_export(sh, param);
		else if (ft_strcmp(head->value[0], "unset") == 0)
			ex_stts = ft_unset(sh, param);
		else
			ex_stts = ft_other_cmd(sh, param);
	}
	return (ex_stts);
}

void	ft_exec(t_sh *sh, t_parms *param)
{
	if (!sh || !param)
		return ;
	if (ft_sh_sz(&sh) == 1)
		ft_router(sh, param);
	else
		ft_piper(sh, param);
}
