/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:53:21 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/23 18:53:20 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/param.h>

typedef struct	s_rdr
{
	int				flag;
	char			*fl_name;
	char			*mode;
	struct s_rdr	*next;
}	t_rdr;

//? MAIN struct
typedef struct s_sh
{
	char			**value;
	char			*type;
	int				in_fd;
	int				out_fd;
	struct s_rdr	*rdr;
	struct s_sh		*next;
}	t_sh;

//? struct that holds the env variables
typedef struct s_env
{
	char			*key;
	char			*value;
	int				visible;
	struct s_env	*next;
}	t_env;

//? params holder struct
typedef struct s_parms
{
	int		ext_stts;
	char	**envp;
	t_env	*env;

	t_env	*exprt_env;
	char	*pwd;
	char	*oldpwd;
	int		ppc_idx;
	int		(*pp_chain)[2];
	int		child_stts[2];

	void	*var;
	void	*tkn;
	size_t	n_file;
	char	*word;
	char	c;
	int		len;
	int		l_len;
	int		v_len;
	int		t_len;
	int		i_qrm;
}	t_parms;


//? struct for the garbage collector
typedef struct s_addr
{
	void			*addr;
	struct s_addr	*next;
}	t_addr;

void	*ft_malloc(size_t size, int mode);
char	**ft_splt(char *str, char sep);
int		ft_len(char *s);
char	*ftm_sjoin(char *s1, char *s2);
int		ft_tlen(char *s[]);
int		ft_strcmp(char *s1, char *s2);
char	*ft_sdup(char *s1);


//! env var class methods
t_env	*ft_env_crt(char *ep[], int flg); //? create a linked list based on the *envp[]
void	ft_env_addb(t_env **lst, t_env *newn);
int		ft_env_sz(t_env	**env);
t_env	*ft_env_lstnew(void *key, void *value, int vsbl);
char	*ft_env_srch(char	*key, t_env	**env); //?search for a specifec value
void	ft_env_prnt(t_env **env); //? print out the link_list
void	ft_env_new(t_env **env, char *key, char *value); //? add new env var
void	ft_env_rmv(t_env **head, char *key); //? remove a specefic var
void	ft_env_dstry(t_env **env); //? destroy all the link_list
char	**ft_env_to_dp(t_env **env); // ? link_list to a *envp[] (for execve)
void	ft_env_updt(t_env **env, char *key, char *new_vl); //? update a env var
t_env	*ft_env_dup(t_env	**env); //? duplicate the initial link_list
t_env	*ft_env_sort(t_env	**env); //?sort the link_list
void	ft_env_prnt_fexprt(t_env **env);
void	ft_env_insrt(t_env **head, char *key, char *value);
int		ft_env_exists(t_env	**env, char *key);

// SH TOOLS
int 	ft_sh_sz(t_sh **sh);
t_sh	*ft_sh_new(t_rdr *rdr, char **value, char *type);
void	ft_sh_addb(t_sh **sh, t_sh *new_sh);
void	ft_sh_rmv(t_sh **sh, char *value);

// Rdr tools
t_rdr	*ft_rdr_new(char *fl_name, char *mode, int flag);
void	ft_rdr_addb(t_rdr **rdr, t_rdr *n_node);
void	prnt_rdr(t_rdr *head);//!exists in main file
void	prnt_sh(t_sh *head);
#endif