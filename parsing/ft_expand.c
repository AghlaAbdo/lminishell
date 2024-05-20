/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/20 20:13:24 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_vars(t_parms *prm, t_var *var)
{
	char	*res;
	t_token	*tkn;
	int		flag;

	flag = 0;
	res = "";
	tkn = (t_token *)prm->tkn;
	prm->t_len = 0;
	while (var)
	{
		join_vars(&tkn, &var, prm, &flag);
		while (var && var->type == 'N')
		{
			ft_token_insrt(&tkn, ft_token_new(var->wrd, 'V', 0));
			tkn = tkn->next;
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
		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'V'));
	else if (token[j])
		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'W'));
	token[*i] = tmp;
}

static void	add_quote(t_var **var, char *token, int *i, char c)
{
	char	tmp_c;
	int		j;

	j = *i;
	if (c != '\'' && c != '"')
		return ;
	(*i)++;
	while (token[*i] && token[*i] != c)
		(*i)++;
	tmp_c = token[*i];
	token[*i] = '\0';
	printf("\n\tto be added: [%s]\n\n", token + j +1);
	if (token[0] != '\'' && ft_strchr(token + j +1, '$'))
		ft_var_addb(var, ft_var_new(my_strdup(token + j +1), 'D'));
	else if (token[0])
		ft_var_addb(var, ft_var_new(my_strdup(token + j +1), 'Q'));
	token[*i] = tmp_c;
	(*i)++;
}

static void	split_tkn(t_parms *prm, t_var *var, char *token, int i)
{
	t_var	*tmp;
	char	*res;

	while (token[i])
	{
		add_word(&var, token, &i);
		add_quote(&var, token, &i, token[i]);
	}
	tmp = var;
	printf("\n--------------- After Split ---------------\n");
	while (tmp)
	{
		printf("tmp value: [%s]\ttype: [%c]\n", tmp->wrd, tmp->type);
		tmp = tmp->next;
	}
	printf("\n-------------------------------------------\n");
	tmp = var;
	while (var)
	{
		prm->var = (t_var *)var;
		if (var->type == 'V' || var->type == 'D'
			|| var->type == 'N' || var->type == 'L')
		{
			prm->c = var->type;
			res = expand_var(&var, prm, var->wrd, "");
			if (res)
				var->wrd = res;
			while (prm->v_len-- > 1)
				var = var->next;
		}
		var = var->next;
	}
	add_vars(prm, tmp);
}

void	ft_expand(t_token *token, t_parms *prm)
{
	t_token	*tkn;
	char	*res;

	tkn = token;
	while (tkn)
	{
		prm->tkn = (t_token *)tkn;
		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<")))
		{
			res = tkn->token;
			split_tkn(prm, NULL, res, 0);
			while (prm->t_len-- > 1)
			{
				printf("ft_expand skipped: [%s]\n", tkn->token);
				tkn = tkn->next;
			}
		}
		if (tkn)
			tkn = tkn->next;
	}
}
