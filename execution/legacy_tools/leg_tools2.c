/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leg_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:37:29 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/23 18:40:39 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


void	ft_exprt_error(t_parms *param, char *s)
{
	write(2, "export: `", 9);
	write(2, s, ft_len(s));
	write(2, "': not a valid identifier\n", 26);
	param->ext_stts = 1;
}

int ft_insrt_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}
