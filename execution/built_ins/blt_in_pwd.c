/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:29:16 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/17 07:46:52 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_is_option(char	*cmd)
{
	return (cmd[0] == '-');
}

static void	ft_norm_pwd(t_parms *param, char *str, int es, int flag)
{
	param->ext_stts = es;
	if (!flag)
		printf("%s\n", str);
	else if (flag == 1)
	{
		write(2, "\033[1;31m error : pwd command should take ", 41);
		write(2, "no options !\033[0m\n", 18);
	}
	else
		perror(str);
}

int	ft_pwd(t_sh *sh, t_parms *param)
{
	char	*path;
	char	*svpath;

	path = NULL;
	svpath = ft_sdup(param->pwd);
	// path = getcwd(NULL, MAXPATHLEN);
	path = ft_gt_pth(NULL, 0);
	if (!path)
		path = svpath;
	if (!sh || !param)
		return (1);
	if (path != NULL)
	{
		if (ft_tlen(sh->value) == 1)
			ft_norm_pwd(param, path, 0, 0);
		else if (ft_is_option(sh->value[1]))
			ft_norm_pwd(param, NULL, 1, 1);
		else
			ft_norm_pwd(param, path, 0, 0);
		free(path);
	}
	else
		ft_norm_pwd(param, "getcwd", 2, 2);
	return (param->ext_stts);
}
