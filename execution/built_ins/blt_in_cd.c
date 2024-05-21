/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_in_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:32:45 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/16 18:20:32 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_gt_pth(char *tojoin, int doit)//!checked
{
	static char	sv_pwd[MAXPATHLEN];
	char		*cwd;
	
	(void)doit;
	cwd = NULL;
	cwd = getcwd(cwd, MAXPATHLEN);
	if (!cwd)//!failed
	{
		if (doit)
		{
			if (errno == ENOENT)
			{
				printf("cd: error retrieving current directory: getcwd:");
				printf(" cannot access parent directories: No such file or directory\n");
			}
			ft_strlcat(sv_pwd, "/", MAXPATHLEN);
			ft_strlcat(sv_pwd, tojoin  , MAXPATHLEN);
		}
	}
	else//!success
		ft_strlcpy(sv_pwd, cwd, MAXPATHLEN); 
	return (ft_sdup(sv_pwd));
}

static void	ft_cd_no_params(t_sh *sh, t_parms *param)//!checked
{
	char	*path;

	if (!sh || !param)
		return ;
	param->ext_stts = 1;
	path = ft_env_srch("HOME", &param->env);
	param->oldpwd = ft_gt_pth(sh->value[1], 1);

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
		param->pwd = ft_gt_pth(sh->value[1], 1);
		ft_env_updt(&param->env, "PWD", param->pwd);
		ft_env_updt(&param->exprt_env, "PWD", param->pwd);
		param->ext_stts = 0;
	}
}

static void	ft_cd_swap(char **old, char **curr)
{
	char	*swap;

	swap = *old;
	*old = *curr;
	*curr = swap;
}

static void	ft_previous_location(t_sh *sh, t_parms *param)//!checked
{
	if (!sh || !param)
		return ;
	if (!param->oldpwd)
		write(2, "cd: OLDPWD not set\n", 20);
	else
	{
		if (chdir(param->oldpwd) == -1)
			perror("cd");
		else
		{
			ft_cd_swap(&param->oldpwd, &param->pwd);
			ft_env_updt(&param->env, "PWD", param->pwd);
			ft_env_updt(&param->env, "OLDPWD", param->oldpwd);
			ft_env_updt(&param->exprt_env, "PWD", param->pwd);
			ft_env_updt(&param->exprt_env, "OLDPWD", param->oldpwd);
			printf("%s\n", param->pwd);
			param->ext_stts = 0;
		}
	}
}

static void	ft_new_path(t_sh *sh, t_parms *param)//!checked
{
	if (!sh || !param)
		return ;
	param->oldpwd = getcwd(NULL, MAXPATHLEN);
	// param->oldpwd = ft_gt_pth(sh->value[1], 0);
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
		ft_previous_location(sh, param);
	else
		ft_new_path(sh, param);
	// prnt_env(param->env);
	return (param->ext_stts);
}
