/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:40:41 by srachidi          #+#    #+#             */
/*   Updated: 2024/04/21 20:03:40 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../main/minishell.h"
# include <stdio.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"

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

//	History funcs
t_histr	*ft_hist_new(char *line);
void	ft_hist_addb(t_histr **histr, t_histr *new);
void	ft_hist_rmvlast(t_histr **histr);
void	ft_add_histr(t_histr **histr);

//	Expanding
char	*ft_expand(char *prompt, t_parms *prm);
char	*expand_it(char *prompt, t_parms *prm, char c, int i);
char	*get_prev(char *prompt);
char	*get_rest(char *prompt, int i);
char	*ft_trim(char *prompt, int j);

//	Handle_quotes
char	*handle_quotes(t_histr **histr, char *input);
char	*keep_reading(t_histr **histr, char *input, char *c, int i);
int		count_quotes(char *input, char *c);

#endif