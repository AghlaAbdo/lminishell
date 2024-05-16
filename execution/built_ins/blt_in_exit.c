/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:51:20 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/10 09:11:43 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_only_digits(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return 0;
		i++;
	}
	return 1;
}


int	ft_exit(char **cmd, t_parms *param)
{
	long long	ex_sts;

	param->ext_stts = 1;
	ex_sts = 0;
	printf("exit\n");
	if (ft_tlen(cmd) == 1)
	{
		param->ext_stts = 0;
		exit (ex_sts);
	}
	else if (ft_tlen(cmd) > 2)
		write(2, "exit: too many arguments\n", 26);
	else if (ft_tlen(cmd) == 2)
	{
		if (!ft_only_digits(cmd[1]))
		{
			write(2, "exit: ", 7);
			write(2, cmd[1], ft_len(cmd[1]));
			write(2, " : numeric argument required\n", 29);
			param->ext_stts = 255;
			exit (param->ext_stts);
		}
		else
		{
			ex_sts = ft_ext_atoi(cmd[1]);
			if (ex_sts >= 0)
			{
				if (ex_sts >= 0 && ex_sts <= 255)
					exit (ex_sts);
				else if (ex_sts >= 256 && ex_sts <= 999999999999999999)
					exit (ex_sts % 256);
				else if (ex_sts > 9223372036854775807)
				{
					write(2, "exit: ", 7);
					write(2, cmd[1], ft_len(cmd[1]));
					write(2, " : numeric argument required\n", 29);
					exit (255);
				}
				exit (255);
			}
			else
			{
				if (ex_sts <= -1 && ex_sts >= -999999999999999999)
					exit (256 + (ex_sts % 256));
			}
		}
	}
	return (param->ext_stts);
}

//! 10000000000000000000 => out of range
//! 1000000000000000000 => in range
//! 9999999999999999999 => out of range
//! 8888888888888888888 => in range
//! 9000000000000099999 => in range
//! 9000000000009999999 => in
//! 9000000099999999999 => in
//! 9000999999999999999 => in
//! 9099999999999999999 => in
//! 9999999999999999999 => out
//! 9200000000000000000 => in
//! 9220000000000000000 => in
//! 9223000000000000000 => in
//! 9223300000000000000 => in
//! 9223370000000000000 => in
//! 9223372000000000000 => in
//! 9223372000000000000 => in
//! 9223372030000000000 => in
//! 9223372036000000000 => in
//! 9223372036800000000 => in
//! 9223372036850000000 => in
//! 9223372036854000000 => in
//! 9223372036854700000 => in
//! 9223372036854770000 => in
//! 9223372036854775000 => in
//! 9223372036854775800 => in
//! 9223372036854775800 => in
//! 9223372036854775807 => in
//! 9223372036854775808 => OUT