/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:28:47 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/05 03:27:13 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_env(t_parms params, t_sh **sh)
{
	t_sh	*head;

	head = *sh;
	if (ft_sh_sz(sh) > 1)
		ft_env_prnt(&params.env);
		
}
