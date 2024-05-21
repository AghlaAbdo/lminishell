/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:28:47 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/17 19:27:10 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


int	ft_env(t_sh *sh, t_parms *param)
{
	t_sh	*head;
	t_env	*phead;

	if (!sh || !param)
		return (0);
	head = sh;
	if (!param->env)
	{
		write(2, "env: No such file or directory\n", 32);
		param->ext_stts = 127;
	}
	phead = param->env;
	if (ft_tlen(head->value) == 1)
	{
		ft_env_prnt(&phead);
		param->ext_stts = 0;
	}
	else
	{
		param->ext_stts = 127;
		write(2, "\033[1;31m error : env command should take ", 41);
		write(2, "no arguments or options !\033[0m\n", 31);
	}
	return (param->ext_stts);
}
