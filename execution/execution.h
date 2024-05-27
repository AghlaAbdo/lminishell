/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:01:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/27 15:57:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../main/minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

char		*ft_strjoin(char *s1, char *s2);
long long	ft_ext_atoi(char *s);
int			ft_valid_identifier(char *s);
char		*ft_substr(char *s, int start, int len);
void		ft_exprt_error(t_parms *param, char *s);
int			ft_only_quotes(char *s);
int			ft_insrt_strcmp(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
int			ft_is_there_slash(char *cmd);
int			ft_is_dir(char *path);

//?main function
void	ft_exec(t_sh *sh, t_parms *param);

//? BUILT-INS
int		ft_env(t_sh *sh, t_parms *param);
int		ft_pwd(t_sh *sh, t_parms *param);
int		ft_echo(t_sh *sh, t_parms *param);
int		ft_cd(t_sh *sh, t_parms *param);
int		ft_exit(char **cmd, t_parms *param);
int		ft_export(t_sh *sh, t_parms *param);
int		ft_unset(t_sh *sh, t_parms *param);
char	*ft_gt_pth(char *tojoin, int doit);

//? PIPELINING
char	**ft_pp_split(char *str, int flag);
int		ft_other_cmd(t_sh *sh, t_parms *param);
char	*ft_pp_join(char *s1, char *s2, char *s3);
char	*ft_path_parser(char **envp, char *cmd, t_parms *param);
void	ft_piper(t_sh *sh, t_parms *param);
void	ft_perror(char *message);
void	ft_norm_close(int (*pp_chain)[2] , int fd);
void	ft_norm_sclose(int (*pp_chain)[2] , int fd);
void	ft_norm_ext_stts(t_parms * param);
void	ft_norm_child_stts(t_sh *curr_sh, t_parms * param, int stts);
void	ft_norm_err_msg(char **cmd, int errno_nbr, char *msg);
int		(*ft_pp_chain_creator(t_sh *sh))[2];
void	ft_fds_collector(t_parms *param, int leng, int norm_i);
int		ft_router(t_sh *sh, t_parms *param);
int		ft_is_builtin(char *cmd);
void	ft_norm_dclose(int fd1, int fd2);
void	ft_norm_nfound_cmd(t_sh *curr_sh);
void	ft_norm_dup2_out(t_sh *curr_sh, t_parms *param);
void	ft_norm_dup2_in(t_sh *curr_sh, t_parms *param);
void	ft_resolve_redirs(t_parms *param, t_sh *sh);
void	ft_open_close(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg);
void	ft_close_ppchain(t_parms *param, t_sh *sh);
void	ft_redirs_bad_inf(t_rdr * rdrs, t_sh *sh, t_parms *param, int err);
void	ft_sngl_cmd_rdr_strms(t_sh *sh);
int	ft_handle_built_redirs(t_sh *sh, t_parms *param);

//!just for interactive testing
t_sh	*ft_exec_parser(char *line);
void	p2d(char **var);
int		ft_pp_chain_len(t_sh *sh);
void	prnt_env(t_env *head);
void 	ft_handler(int sig);

#endif