/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:40:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/05/31 08:50:54 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../main/minishell.h"
# include <stdio.h>
# include <unistd.h>

//  For storing tokens
typedef struct s_token
{
	char			*token;
	char			type;
	// int				lst_len;
	// int				skp;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

// for var quote removal
//	if_f: is it firts in token, AKA space before. /
//		to handle ($, $"", $'')
typedef struct s_var
{
	char			*wrd;
	char			type;
	int				is_f;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

t_sh	*ft_parser(char *input, t_parms *prms);
char	**my_split(char const *s, char c);
char	*ft_pstrjoin(char *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*my_strdup(const char *s1);
char	*ft_itoa(int n);

// void	clean_exit(void);

//	Parsing input
t_token	*parse_input(t_token *token, char *input, char *word, int i);

//	t_hoken tools
t_token	*ft_token_new(char *word, char type);
void	ft_token_addb(t_token **head, t_token *new);
void	ft_token_insrt(t_token **head, t_token *new);
void	ft_token_rmv(t_token **head, t_token *rmv);

//	t_var tools
t_var	*ft_var_new(char *wrd, char type, int is_f);
void	ft_var_addb(t_var **head, t_var *new);
void	ft_var_insrt(t_var **head, t_var *new);
void	ft_var_rmv(t_var **head);

//	Expanding
void	ft_expand(t_token **head, t_parms *prm, t_var *var, t_token *tkn);
char	*expand_var(t_var **var_t, t_parms *prm, char *token, char *res);
char	*expand_it(char *wd, t_parms *prm, int i);
void	join_vars(t_token **head, t_token **curr, t_var **var, t_parms *prm);
char	*get_prev(char *word, int i);
char	*ft_trim(char *word, int j);
char	*get_n_var(t_parms *prm, char *word, char *var, int i);
char	*splt_var(t_parms *prm, char **arr, char *bef, char *aft);
int		check_splt(t_token *tkn, char *value);
char	*check_vlid_var(t_parms *prm, char *wd, int i, int *j);
char	*expand_heredoc(char *token, t_parms *prms);
char	*check_n_file(t_parms *prm, char *wd, int i, int j);
char	*dollar_var(t_parms *prm, char *wd, int *i);
void	skip_var_name(char *wd, int *j);

//	Handle_quotes
void	rmv_char(char *token);

// Here_doc
int		here_doc(t_token *tkn, t_parms *prm);

// Tokenization
t_sh	*ft_tokenization(t_sh *sh, t_token *tkn, char **cmd, int i);

#endif