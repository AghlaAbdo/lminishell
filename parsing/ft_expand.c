/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:22 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


//	add vars to t_token
// flag is to check and replace the first node in t_token
static void	add_vars(t_token **head, t_parms *prm, t_var *var)
{
	char	*res;
	t_token	*curr;
	int		flag;

	flag = 0;
	res = "";
	curr = (t_token *)prm->tkn;
	prm->t_len = 0;
	while (var)
	{
		join_vars(head, &curr, &var, prm, &flag);
		while (var && var->type == 'N')
		{
			ft_token_insrt(&curr, ft_token_new(var->wrd, 'V'));
			curr = curr->next;
			prm->t_len++;
			var = var->next;
			flag = 1;
		}
	}
}

static void	add_word(t_var **var, char *token, int *i)
{
	char	tmp;
	int		j;

	j = *i;
	if (!token[j] || token[j] == '"' || token[j] == '\'')
		return ;
	while (token[*i] && token[*i] != '\'' && token[*i] != '"')
		(*i)++;
	tmp = token[*i];
	token[*i] = '\0';
	if (token[j] && ft_strchr(token + j, '$'))
		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'V', 0));
	else if (token[j])
		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'W', 0));
	token[*i] = tmp;
}

static void	add_quote(t_var **var, char *token, int *i, char c)
{
	char	tmp_c;
	int		is_f;
	int		j;

	j = *i;
	if (c != '\'' && c != '"')
		return ;
	is_f = 0;
	if (*i == 0)
		is_f = 1;
	(*i)++;
	while (token[*i] && token[*i] != c)
		(*i)++;
	tmp_c = token[*i];
	token[*i] = '\0';
	if (c != '\'' && ft_strchr(token + j +1, '$'))
		ft_var_addb(var, ft_var_new(my_strdup(token + j +1), 'D', is_f));
	else if (token[0])
		ft_var_addb(var, ft_var_new(my_strdup(token + j +1), 'Q', is_f));
	token[*i] = tmp_c;
	(*i)++;
}

static void	split_tkn(t_token **tkn, t_parms *prm, t_var *var, char *token)
{
	t_var	*head;
	char	*res;

	head = var;
	while (var)
	{
		prm->var = (t_var *)var;
		if (var->type == 'V' || var->type == 'D'
			|| var->type == 'N' || var->type == 'L')
		{
			prm->c = var->type;
			prm->v_len = 0;
			res = expand_var(&var, prm, var->wrd, "");
			if (res)
				var->wrd = res;
			while (var && prm->v_len-- > 1)
				var = var->next;
		}
		var = var->next;
	}
}

void	ft_expand(t_token **head, t_parms *prm, t_var *var)
{
	t_token	*tkn;
	int		i;

	tkn = *head;
	while (tkn)
	{
		prm->tkn = (t_token *)(tkn);
		if (tkn->type != '>' && tkn->type != '<' && tkn->type != '|'
			&& (!(tkn)->prev || ft_strcmp((tkn)->prev->token, "<<")))
		{
			prm->t_len = 0;
			i = 0;
			var = NULL;
			while (tkn->token[i])
			{
				add_word(&var, tkn->token, &i);
				add_quote(&var, tkn->token, &i, tkn->token[i]);
			}
			split_tkn(head, prm, var, tkn->token);
			add_vars(head, prm, var);
			while (tkn && prm->t_len-- > 1)
				tkn = tkn->next;
		}
		if (tkn)
			tkn = tkn->next;
	}
}
