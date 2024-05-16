/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:11:49 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/14 20:42:27 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_fl_name(t_parms *prm, int *fd)
{
	char	*fl_name;

	fl_name = ft_pstrjoin("/tmp/.hr_fl_", ft_itoa(prm->n_file));
	while (!access(fl_name, F_OK))
	{
		prm->n_file++;
		fl_name = ft_pstrjoin("/tmp/.hr_fl_", ft_itoa(prm->n_file));
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

void	read_heredoc(t_token *tkn, t_parms *prm, char *limit, int quots)
{
	char	*line;
	char	*res;
	char	*fl_name;
	int		fd;

	fl_name = get_fl_name(prm, &fd);
	prm->n_file++;
	if (ft_strchr(limit, '"') || ft_strchr(limit, '\''))
		quots = 1;
	rmv_char(limit);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limit))
			break ;
		res = line;
		if (!quots)
			res = expand_heredoc(res, prm);
		write(fd, res, ft_len(res));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	tkn->next->token = fl_name;
}

void	here_doc(t_token *tkn, t_parms *prm)
{
	while (tkn)
	{
		if (tkn->type == '<' && ft_len(tkn->token) > 1)
		{
			read_heredoc(tkn, prm, tkn->next->token, 0);
		}
		tkn = tkn->next;
	}
}
