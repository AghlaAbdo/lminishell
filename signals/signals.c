/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:39 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 09:21:17 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_updt_stts(int status, t_parms *param, struct termios state)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putstr_fd("Quit: 3\n", 2);
		param->ext_stts = WTERMSIG(status) + 128;
		tcsetattr(STDOUT_FILENO, 0, &state);
	}
	if (WIFEXITED(status))
		param->ext_stts = WEXITSTATUS(status);
}

void 	ft_handler(int sig)
{
	if (sig == SIGINT && !g_inchild)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig != SIGQUIT)
		write(1, "\n", 1);
}

void ft_handler_redirect(int sig)
{
	if (g_inchild)
	{
		g_inchild = 0;
		return ;
	}
	ft_handler(sig);
}


