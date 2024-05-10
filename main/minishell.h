/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:16:22 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/05 00:49:16 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_rdr
{
	char			*fl_name;
	char			*mode;
	struct s_rdr	*next;
}					t_rdr;

//? MAIN struct
typedef struct s_sh
{
	char		**value;
	char		*type;
	t_rdr		*rdr;
	struct s_sh	*next;
}	t_sh;

//? struct that holds the env variables
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//?	For readline history
typedef struct	s_histr
{
	char			*line;
	struct s_histr	*next;
}				t_histr;

//? params holder struct
typedef struct s_parms
{
	int		ext_stts;
	char	**envp;
	t_env	*env;
	t_histr	*histr;

	size_t	n_file;
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
t_env	*ft_env_crt(char *ep[]); //? create a linked list based on the *envp[]
void	ft_env_addb(t_env **lst, t_env *newn);
int		ft_env_sz(t_env	**env);
t_env	*ft_env_lstnew(void *key, void *value);
char	*ft_env_srch(char	*key, t_env	**env); //?search for a specifec value
void	ft_env_prnt(t_env **env); //? print out the link_list
void	ft_env_new(t_env **env, char *key, char *value); //? add new env var
void	ft_env_rmv(t_env **head, char *key); //? remove a specefic var
void	ft_env_dstry(t_env **env); //? destroy all the link_list
char	**ft_env_to_dp(t_env **env); // ? link_list to a *envp[] (for execve)
void	ft_env_updt(t_env **env, char *key, char *new_vl); //? update a env var
t_env	*ft_env_dup(t_env	**env); //? duplicate the initial link_list
t_env	*ft_env_sort(t_env	**env); //?sort the link_list


// SH TOOLS
int 	ft_sh_sz(t_sh **sh);
t_sh	*ft_sh_new(t_rdr *rdr, char **value, char *type);
void	ft_sh_addb(t_sh **sh, t_sh *new_sh);
void	ft_sh_rmv(t_sh **sh, char *value);

#endif