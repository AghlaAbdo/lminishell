/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:44:48 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/29 15:19:16 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_is_there_slash(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '/' || cmd[i] == '.'
			|| (cmd[i] == '.' && cmd[i + 1] == '.'))
			return (1);
	}
	return (0);
}

char	*ft_get_path(char **envp)
{
	int		i;
	char	*path;

	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (ft_strncmpx("PATH", envp[i], 4) == 0)
			path = ft_substr(envp[i], 5, ft_len(envp[i]));
	}
	return (path);
}

char	**ft_get_locations(char *path, char *cmd)
{
	char	**pthnms;
	int		i;
	char	*tmp;

	i = -1;
	if (!path)
		return (NULL);
	pthnms = ft_pp_split(path, 0);
	while (pthnms[++i])
	{
		tmp = pthnms[i];
		pthnms[i] = ft_pp_join(pthnms[i], "/", cmd);
	}
	i = 0;
	return (pthnms);
}

static void	ft_norm_path_pars(char *cmd)
{
	write(2, "lminishell :", 13);
	write(2, cmd, ft_len(cmd));
	write(2, ": No such file or directory\n", 29);
	exit(127);
}

char	*ft_path_parser(char **envp, char *cmd, t_parms *param)
{
	char	*path;
	char	**bin_dirs;
	int		i;

	(void)envp;
	i = -1;
	if (ft_is_there_slash(cmd))
		return (cmd);
	if (!(*envp))
		path = ft_env_srch("PATH", &param->env);
	else
		path = ft_get_path(ft_env_to_dp(&param->env));
	bin_dirs = ft_get_locations(path, cmd);
	if (!bin_dirs)
		ft_norm_path_pars(cmd);
	while (bin_dirs[++i])
	{
		if (access(bin_dirs[i], F_OK | X_OK) == 0)
			return (bin_dirs[i]);
	}
	return (NULL);
}
