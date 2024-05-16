/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:44:48 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/02 15:49:28 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_is_there_slash(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '/' || cmd[i] == '.')
			return (1);
	}
	return (0);
}

char	*ft_get_path(char **envp)
{
	int		i;
	char	*path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
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
	pthnms = ft_pp_split(path, 0);
	while (pthnms[++i])
	{
		tmp = pthnms[i];
		pthnms[i] = ft_pp_join(pthnms[i], "/", cmd);
	}
	i = 0;
	return (pthnms);
}

char	*ft_path_parser(char **envp, char *cmd)
{
	char	*path;
	char	**bin_dirs;
	int		i;

	i = -1;
	if (ft_is_there_slash(cmd))
		return (cmd);
	path = ft_get_path(envp);
	bin_dirs = ft_get_locations(path, cmd);
	while (bin_dirs[++i])
	{
		if (access(bin_dirs[i], F_OK | X_OK) == 0)
			return (bin_dirs[i]);
	}
	return (NULL);
}

