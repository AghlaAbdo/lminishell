/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:40:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/29 23:39:27 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../main/minishell.h"
# include <stdio.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"

//  For storing tokens
typedef struct	s_token
{
	char			*token;
	char			type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token; 

t_sh	*ft_parser(char *input, t_parms *prms);
char	**my_split(char const *s, char c);
int		word_len(char const *str, char *c);
void	skip_word(char const **s, char c);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*my_strdup(const char *s1);

void	clean_exit(void);

//	Parsing input
t_token	*parse_input(t_token *token, char *input, char *word, int i);

//	History funcs
t_histr	*ft_hist_new(char *line);
void	ft_hist_addb(t_histr **histr, t_histr *new);
void	ft_hist_rmvlast(t_histr **histr);
void	ft_add_histr(t_histr **histr);

//	t_hoken tools
t_token	*ft_token_new(char *word, char type);
void	ft_token_addb(t_token **head, t_token *new);

//	Expanding
void	ft_expand(t_token **token, t_parms *prm);
char	*expand_it(char *word, t_parms *prm, char c, int i);
char	*get_prev(char *word, int i);
char	*get_rest(char *word);
char	*ft_trim(char *word, int j);

//	Handle_quotes
char	*handle_quotes(t_histr **histr, char *input);
char	*keep_reading(t_histr **histr, char *input, char *c, int i);
int		count_quotes(char *input, char *c);

#endif