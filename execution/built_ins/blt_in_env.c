/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:28:47 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 12:41:33 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_norm_env(t_parms *param)
{
	param->ext_stts = 127;
	write(2, "\033[1;31m subject error : env command should take ", 49);
	write(2, "no arguments or options !\033[0m\n", 31);
}

int	ft_env(t_sh *sh, t_parms *param)
{
	t_sh	*head;
	t_env	*phead;

	if (!sh || !param)
		return (0);
	head = sh;
	phead = NULL;
	if (!param->env)
	{
		ft_env_addb(&phead, ft_env_lstnew("_", "env", 1));
		ft_env_prnt(&phead);
		param->ext_stts = 0;
	}
	phead = param->env;
	if (ft_tlen(head->value) == 1)
	{
		ft_env_prnt(&phead);
		param->ext_stts = 0;
	}
	else
		ft_norm_env(param);
	return (param->ext_stts);
}
