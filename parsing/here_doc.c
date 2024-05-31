/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:11:49 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/31 08:50:30 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <signal.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	rmv_char(char *token)
{
	char	*res;
	char	c;

	res = token;
	while (*token)
	{
		if (*token == '\'' || *token == '"')
		{
			c = *token;
			token++;
			while (*token != c)
				*res++ = *token++;
			token++;
		}
		if (*token && *token != '\'' && *token != '"')
		{
			*res = *token;
			res++;
			token++;
		}
	}
	*res = '\0';
}

char	*get_fl_name(t_parms *prm, int *fd)
{
	char	*fl_name;

	fl_name = ft_pstrjoin("/tmp/.hr_fl_", ft_itoa(prm->n_file));
	prm->n_file++;
	while (!access(fl_name, F_OK))
	{
		fl_name = ft_pstrjoin("/tmp/.hr_fl_", ft_itoa(prm->n_file));
		prm->n_file++;
	}
	*fd = open(fl_name, O_CREAT | O_RDWR, 0600);
	if (fd < 0)
	{
		ft_malloc(0, 1);
		perror("open");
		exit(1);
	}
	return (fl_name);
}

void	pr_handler(int s)
{
	if (s == SIGINT)
		close(0);
}

int	read_heredoc(t_token *tkn, t_parms *prm, char *limit, int quots)
{
	char	*line;
	char	*res;
	int		fd;

	tkn->next->token = get_fl_name(prm, &fd);
	if (ft_strchr(limit, '"') || ft_strchr(limit, '\''))
		quots = 1;
	rmv_char(limit);
	while (1)
	{
		line = readline("> ");
		if (!ttyname(0))
			return (open(ttyname(2), O_RDWR), close(fd), 1);
		if (!line || !ft_strcmp(line, limit))
			break ;
		res = line;
		if (!quots)
			res = expand_heredoc(res, prm);
		write(fd, res, ft_len(res));
		write(fd, "\n", 1);
		free(line);
	}
	return (close(fd), free(line), 0);
}

int	here_doc(t_token *tkn, t_parms *prm)
{
	while (tkn)
	{
		if (tkn->type == '<' && ft_len(tkn->token) > 1)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGINT, pr_handler);
			if (read_heredoc(tkn, prm, tkn->next->token, 0))
			{
				prm->ext_stts = 1;
				return (1);
			}
		}
		tkn = tkn->next;
	}
	return (0);
}
