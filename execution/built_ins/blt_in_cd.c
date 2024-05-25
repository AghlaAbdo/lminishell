/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:32:45 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/25 18:54:28 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_gt_pth(char *tojoin, int doit)
{
	static char	sv_pwd[MAXPATHLEN];
	char		cwd[MAXPATHLEN];

	if (getcwd(cwd, MAXPATHLEN) == NULL)
	{
		if (doit)
		{
			printf("doit\n");
			if (errno == ENOENT)
			{
				printf("cd: error retrieving current directory: getcwd:");
				printf(" cannot access parent directories: No such file or directory\n");
			}
			ft_strlcat(sv_pwd, "/", MAXPATHLEN);
			ft_strlcat(sv_pwd, tojoin  , MAXPATHLEN);
		}
	}
	else
		ft_strlcpy(sv_pwd, cwd, MAXPATHLEN); 
	return (ft_sdup(sv_pwd));
}

static void	ft_cd_no_params(t_sh *sh, t_parms *param)
{
	char	*path;

	if (!sh || !param)
		return ;
	param->ext_stts = 1;
	path = ft_env_srch("HOME", &param->env);
	param->oldpwd = ft_gt_pth(NULL, 0);

	if (!ft_env_srch("OLDPWD", &param->env))
		ft_env_new(&param->env, "OLDPWD", param->oldpwd);
	else
		ft_env_updt(&param->env, "OLDPWD", param->oldpwd);
	if (!ft_env_srch("OLDPWD", &param->exprt_env))
		ft_env_insrt(&param->exprt_env, "OLDPWD", param->oldpwd);
	else
		ft_env_updt(&param->exprt_env, "OLDPWD", param->oldpwd);
	if (chdir(path) == -1)
		write(2, "cd: HOME not set\n", 18);
	else
	{
		char *ppp = ft_gt_pth(NULL,0);
		ft_env_updt(&param->env, "PWD", ppp);
		ft_env_updt(&param->exprt_env, "PWD", ppp);
		param->ext_stts = 0;
	}
}

static void	ft_previous_location(void)
{
	write(2, "\033[1;31m subject error : cd with only ", 38);
	write(2, "a relative or absolute path !\033[0m\n", 35);
}

static void	ft_new_path(t_sh *sh, t_parms *param)//!checked
{
	if (!sh || !param)
		return ;
	param->oldpwd = ft_gt_pth(sh->value[1], 1);
	if (!ft_env_srch("OLDPWD", &param->env))
		ft_env_new(&param->env, "OLDPWD", param->oldpwd);
	else
		ft_env_updt(&param->env, "OLDPWD", param->oldpwd);
	if (!ft_env_srch("OLDPWD", &param->exprt_env))
		ft_env_insrt(&param->exprt_env, "OLDPWD", param->oldpwd);
	else
		ft_env_updt(&param->exprt_env, "OLDPWD", param->oldpwd);

	if (chdir(sh->value[1]) == -1)
		perror(ft_strjoin("cd: ", sh->value[1]));
	else
	{
		param->pwd = ft_gt_pth(sh->value[1], 1);
		ft_env_updt(&param->env, "PWD", param->pwd);
		ft_env_updt(&param->exprt_env, "PWD", param->pwd);
		param->ext_stts = 0;
	}
}

int	ft_cd(t_sh *sh, t_parms *param)
{
	if (!sh || !param)
		return (0);
	param->ext_stts = 1;
	if (ft_tlen(sh->value) == 1 || ft_strcmp(sh->value[1], "~") == 0)
		ft_cd_no_params(sh, param);
	else if (ft_strcmp(sh->value[1], "-") == 0)
		ft_previous_location();
	else
		ft_new_path(sh, param);
	return (param->ext_stts);
}
