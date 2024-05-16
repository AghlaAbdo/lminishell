// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_parstester.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/06 01:22:47 by srachidi          #+#    #+#             */
// /*   Updated: 2024/05/14 18:19:41 by srachidi         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../execution/execution.h"
// #include "minishell.h"
// #include <stdio.h>

// static int	set_checker(char *str, char to_find)
// {
// 	while (*str)
// 	{
// 		if (*str == to_find)
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

// char	*ft_strtrim(char *s1, char *set)
// {
// 	int		i;
// 	int		j;
// 	char	*trimmed;

// 	i = 0;
// 	j = ft_len(s1) - 1;
// 	while (s1[i])
// 	{
// 		if (set_checker(set, s1[i]) == 0)
// 			break ;
// 		i++;
// 	}
// 	while (j > 0)
// 	{
// 		if (set_checker(set, s1[j]) == 0)
// 			break ;
// 		j--;
// 	}
// 	trimmed = ft_substr(s1, i, (j - i) + 1);
// 	return (trimmed);
// }

// void p2d(char **var)
// {
// 	if (var == NULL) {
// 		printf("NULL\n");
// 		return;
// 	}

// 	while (*var != NULL) {
// 		printf("{%s}\n", *var);
// 		var++;
// 	}
// }

// // t_rdr	*ft_simulate_redirections(void)
// // {
// // 	t_rdr *res;

// // 	res = ft_rdr_new("a", "out");
// // 	ft_rdr_addb(&res, ft_rdr_new("b", "out"));
// // 	ft_rdr_addb(&res, ft_rdr_new("c", "out"));
// // 	return (res);
// // }

// t_sh	*ft_exec_parser(char *line)
// {
// 	char	**res = ft_splt(line,'+');
// 	int		i = -1;
// 	t_sh	*sh = NULL;
// 	// t_rdr *out_redirs = ft_simulate_redirections();

// 	while (res[++i])
// 	{
// 		if (!ft_strcmp(res[i], "|"))
// 			ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_splt(res[i], ' ')[0], ' '), "PIPE", NULL));
// 		else
// 		{
// 			// if (!ft_strcmp(ft_strtrim(res[i], " "), "cat"))
// 			// 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_strtrim(res[i], " "), ' ') , "CMD", ft_rdr_new("Makefile", "in")));
// 			// else if(!ft_strcmp(ft_strtrim(res[i], " "), "grep NAME"))
// 			// 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_strtrim(res[i], " "), ' ') , "CMD", NULL));
// 			// else 
// 			// 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_strtrim(res[i], " "), ' ') , "CMD", out_redirs));
// 			// else 
// 				ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_strtrim(res[i], " "), ' ') , "CMD", NULL));
// 		}

// 		//? if (ft_strcmp(res[i], "|") == 0)
// 		//? 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_splt(res[i], ' ')[0], ' '), "PIPE"));
// 		//? else if (ft_strcmp(res[i], "ps") == 0 
// 		//? 		|| ft_strcmp(res[i], "cat") == 0 
// 		//? 		|| ft_strcmp(res[i], "wc") == 0 
// 		//? 		|| ft_strcmp(res[i], "ls") == 0
// 		//? 		|| ft_strcmp(res[i], "env") == 0
// 		//? 		|| ft_strcmp(res[i], "pwd") == 0
// 		//? 		|| ft_strcmp(res[i], "echo") == 0
// 		//? 		|| ft_strcmp(res[i], "cd") == 0
// 		//? 		|| ft_strcmp(res[i], "exit") == 0
// 		//? 		|| ft_strcmp(res[i], "export") == 0
// 		//? 		|| ft_strcmp(res[i], "unset") == 0
// 		//? 		|| ft_strcmp(res[i], "xx") == 0)
// 		//? 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_splt(res[i], ' ')[0], ' '), "CMD"));
// 		//? else if (ft_strcmp(res[i], "<") == 0 ||
// 		//? 		ft_strcmp(res[i], ">") == 0 ||
// 		//? 		ft_strcmp(res[i], ">>") == 0)
// 		//? 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_splt(res[i], ' ')[0], ' '), "REDIR"));
// 		//? else if (ft_strcmp(res[i], "file") == 0)
// 		//? 	ft_sh_addb(&sh, ft_sh_new(ft_splt(ft_splt(res[i], ' ')[0], ' '), "FILE"));
// 	}
// 	// i = 0;
// 	// while (sh)
// 	// {
// 	// 	if (!ft_strcmp(sh->type, "CMD"))
// 	// 	{
// 	// 		while (sh->rdrs)
// 	// 		{
// 	// 			printf("****|%d|****> fl_name = |%s| <>  mode = |%s| \n", i, sh->rdrs->fl_name,  sh->rdrs->mode);
// 	// 			sh->rdrs = sh->rdrs->next;
// 	// 		}
// 	// 		while (sh->value[i] != NULL)
// 	// 		{
// 	// 			printf("====|%d|===> value = |%s| <>  type = |%s| \n", i, sh->value[i],  sh->type);
// 	// 			i++;
// 	// 		}
// 	// 	}
// 	// 	i = 0;
// 	// 	if (!ft_strcmp(sh->type, "PIPE"))
// 	// 		printf("====|%d|===> value = |%s| <>  type = |%s| \n", i, sh->value[0],  sh->type);
// 	// 	sh = sh->next;
// 	// }
// 	// return (NULL);
	
// 	return (sh);
// }