/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:01:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:36:45 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../main/minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

char		*ft_strjoin(char *s1, char *s2);
long long	ft_ext_atoi(char *s, int res, int i, int digit);
int			ft_valid_identifier(char *s);
char		*ft_substr(char *s, int start, int len);
void		ft_exprt_error(t_parms *param, char *s);
int			ft_only_quotes(char *s);
int			ft_insrt_strcmp(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
int			ft_is_there_slash(char *cmd);
int			ft_is_dir(char *path);
int			ft_strncmpx(char *s1, char *s2, size_t n);
//?main function
void		ft_exec(t_sh *sh, t_parms *param, int ambgs_rdr, int sp_fd);
//? BUILT-INS
int			ft_env(t_sh *sh, t_parms *param);
int			ft_pwd(t_sh *sh, t_parms *param);
int			ft_echo(t_sh *sh, t_parms *param, int i, int n_line);
void		ft_putstr(char *s);
int			ft_all_dashes(char *cmd);
int			ft_dasher(char **cmd);
int			ft_args_are_flags(char **cmd);
int			ft_imposter_flag(char **cmd);
int			ft_n_ln_chckr(char *cmd);
int			ft_n_gang(char **cmd);
int			ft_norm_echot(void);
void		ft_norm_echo(t_sh *sh, int n_line, int i, t_parms *param);
void		ft_norm_echo_lif(t_sh *sh, int *i);
int			ft_glued_flags(char **cmd);
int			ft_norm_echo_lelse(t_sh *sh, t_parms *param, int *i);

int			ft_cd(t_sh *sh, t_parms *param);
int			ft_exit(char **cmd, t_parms *param);
int			ft_only_digits(char *s);
int			ft_export(t_sh *sh, t_parms *param, int i, int eq_indx);
void		ft_norm_exprt(t_parms *param, char *s, int eq_indx);
int			ft_isthere_equal(char *s);
void		ft_no_equal_found(char *s, t_parms *param);
void		ft_key_value_export(char *s, t_parms *param, int eq_indx);
int			ft_unset(t_sh *sh, t_parms *param);
char		*ft_gt_pth(char *tojoin, int doit);
void		ft_sngl_cmd_rdr_strms(t_sh *sh);
void		ft_norm_other(t_rdr *rdrs);
void		ft_norm_otherr(t_rdr *rdrs);
void		ft_norm_otherrr(t_rdr *rdrs, t_sh *sh, t_parms *param);
void		ft_handle_redirs(t_sh *sh, t_parms *param);
int			ft_norm_opn_cls(t_rdr *rdrs, t_parms *param, t_sh *sh, int flg);
int			ft_norm_opn_clss(t_rdr *rdrs, t_parms *param, t_sh *sh);
//? PIPELINING
char		**ft_pp_split(char *str, int flag);
int			ft_other_cmd(t_sh *sh, t_parms *param);
char		*ft_pp_join(char *s1, char *s2, char *s3);
char		*ft_path_parser(char **envp, char *cmd, t_parms *param);
void		ft_piper(t_sh *sh, t_parms *param, int leng, pid_t pid);
void		ft_perror(char *message);
void		ft_norm_close(int (*pp_chain)[2], int fd);
void		ft_norm_sclose(int (*pp_chain)[2], int fd);
void		ft_norm_child_stts(t_sh *curr_sh, t_parms *param, int stts);
void		ft_norm_err_msg(char **cmd, int errno_nbr, char *msg);
int			**ft_pp_chain_creator(t_sh *sh);
void		ft_norm_unlink(t_parms *param, t_rdr *rdrs);
int			ft_router(t_sh *sh, t_parms *param, int ex_stts);
int			ft_is_builtin(char *cmd);
void		ft_norm_dclose(int fd1, int fd2);
void		ft_norm_nfound_cmd(t_sh *curr_sh);
void		ft_norm_dup2_out(t_sh *curr_sh, t_parms *param);
void		ft_norm_dup2_in(t_sh *curr_sh, t_parms *param);
void		ft_resolve_redirs(t_parms *param, t_sh *sh, t_rdr	*rdrs);
void		ft_open_close(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg);
void		ft_close_ppchain(t_parms *param, t_sh *sh);
void		ft_redirs_bad_inf(t_rdr *rdrs, t_sh *sh, t_parms *param, int err);
void		ft_sngl_cmd_rdr_strms(t_sh *sh);
int			ft_handle_built_redirs(t_sh *sh, t_parms *param);
int			ft_norm_err_msgg(t_sh *sh, t_parms *param);
int			ft_pp_chain_len(t_sh *sh);
int			ft_blt_rdrs_bad_inf(t_rdr *rdrs, t_sh *sh, t_parms *param, int err);
void		ft_rstr_dflt_strm(int sv_in, int sv_out);
void		ft_fst_pp_exec(t_parms *param, t_sh *curr_sh);
void		ft_mid_pp_exec(t_parms *param, t_sh *curr_sh);
void		ft_lst_pp_exec(t_parms *param, t_sh *curr_sh);
void		ft_fst_pp_forker(t_sh *sh, t_parms *param, t_sh *head);
void		ft_mid_pp_forker(t_sh *sh, t_parms *param, t_sh *head);
pid_t		ft_lst_pp_forker(t_sh *sh, t_parms *param, t_sh *head);
int			ft_blt_opn_cls(t_sh *sh, t_rdr *rdrs, t_parms *param, int flg);
int			ft_norm_hand_red(t_rdr *rdrs, t_parms *param);
int			ft_norm_hand_redd(t_rdr *rdrs, t_sh *sh, t_parms *param);
int			ft_handle_built_redirs(t_sh *sh, t_parms *param);
//?SIGS
void		ft_handler(int sig);
void		ft_handler_redirect(int sig);
//?just 	for interactive testing
void		prnt_env(t_env *head);
#endif