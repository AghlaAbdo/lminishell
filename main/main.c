/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/22 16:04:22 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"
#include "../parsing/parsing.h"

void	ft_parms_init(t_parms *holder, int ac, char *av[], char *ep[])
{
	(void)ac;
	(void)av;
	holder->ext_stts = 0;
	holder->envp = ep;
	holder->env = ft_env_crt(ep);
	holder->histr = NULL;
}

char	*ft_line(int ext_stts)
{
	char	*line;

	if (!ext_stts)
		line = readline("lminishell-0.1$ ");
	else
		line = readline("\033[1;31m{🚫}==>\033[0m");
	if (line)
		;
		// add_history(line);
	else
	{
		rl_on_new_line();
		rl_redisplay();
		printf("exit\n");
		clean_exit();
	}
	return (line);
}

int	main(int ac, char *av[], char *ep[])
{
	t_parms	holder;
	char	*input;
	t_sh	*shel;

	ft_parms_init(&holder, ac, av, ep);
	while (1)
	{
		input = ft_line(holder.ext_stts);
		printf("You entered: %s\n", input);
		shel = ft_parser(input, &holder); //!PARSIG + error handling + explanding
		
		//TODO ft_exec(shel, holder); //! pipes + redirection + built-ins
		free(input);
	}
	rl_clear_history(); //!ignore the error mark
	ft_malloc(0, 1);
	return (0);

}
