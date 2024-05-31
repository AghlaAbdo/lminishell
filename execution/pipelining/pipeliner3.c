/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeliner3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:36:17 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:36:35 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_norm_unlink(t_parms *param, t_rdr *rdrs)
{
	param->ext_stts = 1;
	write(2, rdrs->fl_name, ft_len(rdrs->fl_name));
	write(2, ": ambiguous redirect\n", 22);
	exit (param->ext_stts);
}
