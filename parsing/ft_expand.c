/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
/*   Updated: 2024/05/18 20:22:30 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char	*split_value(t_token **tkn, char *value, char *bef, char *aft)
// {
// 	char	**arr;
// 	int		i;

// 	i = 0;
// 	arr = my_split(value, ' ');
// 	if ((*tkn)->type == 'L')
// 	{
// 		while ((*tkn)->lst_len)
// 		{
// 			i++;
// 			(*tkn)->lst_len--;
// 		}
// 	}
// 	// rmv_char(bef + i);
// 	i = 0;
// 	(*tkn)->token = ft_pstrjoin(bef, arr[i]);
// 	(*tkn)->type = 'V';
// 	while (arr[++i + 1] && (*tkn))
// 	{
// 		ft_token_insrt(tkn, ft_token_new(arr[i], 'V', 0));
// 		(*tkn) = (*tkn)->next;
// 	}
// 	if (!ft_strchr(aft, '$'))
// 		aft = get_prev(aft, -1, 0);
// 	value = ft_pstrjoin(arr[i], aft);
// 	ft_token_insrt(tkn, ft_token_new(value, 'L', ft_len(arr[i])));
// 	return (NULL);
// }

int check_splt(t_token *tkn)
{
	t_token *prv;
	t_token *curr;

	prv = tkn;
	curr = tkn;
	while (prv && prv->prev)
	{
		printf("prv token: [%s]\tprev: [%s]\n", prv->token, prv->prev->token);
		if (!prv->prev || prv->prev->type == '|')
			break;
		prv = prv->prev;
	}
	while (prv && prv != tkn)
	{
		printf("next token: [%s]\n", prv->token);
		if (prv->type == '<' || prv->type == '>')
			prv = prv->next->next;
		else
		{
			printf("here\n");
			if (!ft_strcmp(prv->token, "export"))
			{
				prv = curr;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}

// char	*expand_it(t_token **tkn, char *word, t_parms *prm, int i)
// {
// 	char	*var;
// 	char	*res;
// 	int		j;

// 	j = i +1;
// 	var = ft_trim(word, i +1);
// 	res = check_vlid_var(prm, word, i);
// 	if (res)
// 		return (res);
// 	while (word[j] && ((word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z'))
// 		|| (word[j] >= 'A' && word[j] <= 'Z')
// 		|| (word[j] >= '0' && word[j] <= '9')))
// 		j++;
// 	var = ft_env_srch(var, &prm->env);
// 	if (var && prm->c != '"' && (ft_strchr(var, ' ') || ft_strchr(var, '\t')))
// 		return (split_value(tkn, var, get_prev(word, i, 0), word + j));
// 	if (var)
// 	{
// 		prm->len = ft_len(var);
// 		if (!word[j])
// 			return (var);
// 		res = ft_pstrjoin(var, word + j);
// 		return (res);
// 	}
// 	return (word + j);
// }

// int	expand_quotes(t_parms *prms, char **token, int *i)
// {
// 	char	*res;

// 	prms->word = *token;
// 	(*i)++;
// 	while ((*token)[*i] && (*token)[*i] != '"')
// 	{
// 		if ((*token)[*i] == '$')
// 		{
// 			prms->len = 0;
// 			prms->c = '"';
// 			res = expand_it(NULL, *token, prms, *i);
// 			if (!res)
// 				return (1);
// 			(*token) = ft_pstrjoin(get_prev((*token), *i, '"'), res);
// 			while (prms->len-- > 1)
// 				(*i)++;
// 		}
// 		if ((*token)[*i] != '"' && (*token)[*i] != '$')
// 			(*i)++;
// 	}
// 	(*i)++;
// 	return (0);
// }

// char	*expand_tkn(t_token *tkn, t_parms *prms, char *token, int i)
// {
// 	char	*res;

// 	while (token[i])
// 	{
// 		if (token[i] == '"')
// 			if (expand_quotes(prms, &token, &i))
// 				return (NULL);
// 		skip_sngl_quot(token, &i);
// 		if (token[i] == '$')
// 		{
// 			prms->len = 0;
// 			prms->c = 0;
// 			res = expand_it(&tkn, token, prms, i);
// 			if (!res)
// 				return (NULL);
// 			token = ft_pstrjoin(get_prev(token, i, 0), res);
// 			while (prms->len-- > 1)
// 				i++;
// 		}
// 		if (token[i] && token[i] != '"' && token[i] != '$' && token[i] != '\'')
// 			i++;
// 	}
// 	return (token);
// }

// // expand token, 'i' skips the last splited var token (ex: d")
// // I still need to skip it again in get_prev so I used 'j'
// void	ft_expand(t_token **token, t_parms *prms)
// {
// 	t_token	*tkn;
// 	char	*res;
// 	int		i;
// 	int		j;

// 	tkn = *token;
// 	while (tkn)
// 	{
// 		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<"))
// 			&& ft_strchr(tkn->token, '$') && !ft_strchr(tkn->token, '"')
// 			&& !ft_strchr(tkn->token, '\''))
// 		{
// 			i = 0;
// 			res = tkn->token;
// 			if (tkn->type == 'L')
// 			{
// 				j = tkn->lst_len +1;
// 				while (--j)
// 					i++;
// 			}
// 			res = expand_tkn(tkn, prms, res, i);
// 			if (res)
// 				tkn->token = res;
// 		}
// 		tkn = tkn->next;
// 	}
// }
// while (token[i] && token[i] != '$' && token[i] != '\'' && token[i] != '"')
// 	i++;
// tmp = token[i];
// token[i] = '\0';
// if (token[0])
// 	ft_var_addb(var, ft_var_new(my_strdup(token), 'W'));
// token[i] = tmp;

void add_word(t_var **var, char *token, int *i)
{
	char tmp;
	int j;

	j = *i;
	if (!token[j] || token[j] == '"' || token[j] == '\'')
		return;
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

void add_quote(t_var **var, char *token, int *i, char c)
{
	char tmp;
	int j;

	j = *i;
	if (c != '\'' && c != '"')
		return;
	(*i)++;
	while (token[*i] && token[*i] != c)
		(*i)++;
	(*i)++;
	tmp = token[*i];
	token[*i] = '\0';
	if (token[j] && token[j] != '\'' && ft_strchr(token + j, '$'))
		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'D'));
	else if (token[j])
		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'Q'));
	token[*i] = tmp;
}

char *splt_var(t_parms *prm, t_var **var_tt, char *var, char *bef, char *aft)
{
	char **arr;
	t_var	*var_t;
	t_var *tmp;
	int i;

	(void)prm;
	(void)aft;
	(void)var_tt;
	printf("wassap!!\n");
	var_t = (t_var *)prm->var;
	arr = my_split(var, ' ');
	i = 0;
	var_t->wrd = ft_pstrjoin(bef, arr[i]);
	printf("var_t value join: [%s]\n", var_t->wrd);
	var_t->type = 'N';
	tmp = var_t;
		printf("\t\tvalue: [%s]\n", var_t->wrd);
	while (arr[++i +1] )
	{
		ft_var_insrt(&var_t, ft_var_new(arr[i], 'N'));
		var_t = var_t->next;
		printf("\t\tvalue: [%s]\n", var_t->wrd);
	}
	aft = ft_pstrjoin(arr[i], aft);
	ft_var_insrt(&var_t, ft_var_new(aft, 'N'));
	printf("tmp value: [%s]\n", tmp->wrd);
	return (NULL);
}

char *expand_it(t_var **var_t, char *word, t_parms *prm, int i, char c)
{
	char *var;
	char *res;
	int j;

	(void)c;
	j = i + 1;
	var = ft_trim(word, i + 1);
	res = check_vlid_var(prm, word, i);
	if (res)
		return (res);
	while (word[j] && ((word[j] == '_' || (word[j] >= 'a' && word[j] <= 'z')) || (word[j] >= 'A' && word[j] <= 'Z') || (word[j] >= '0' && word[j] <= '9')))
		j++;
	var = ft_env_srch(var, &prm->env);
	if (var && c == 'V' && !check_splt(prm->tkn) && (ft_strchr(var, ' ') || ft_strchr(var, '\t')))
		return (splt_var(prm, var_t, var, get_prev(word, i), word + j));
	if (var)
	{
		prm->len = ft_len(var);
		if (!word[j])
			return (var);
		res = ft_pstrjoin(var, word + j);
		return (res);
	}
	return (word + j);
}

char *expand_tkn(t_var **var_t, t_parms *prm, char *token, int i, char c)
{
	// char	*var;
	char *res;
	int j;

	res = "";
	j = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			res = expand_it(var_t, token, prm, i, c);
			if (!res)
				return (NULL);
			token = ft_pstrjoin(get_prev(token, i), res);
			while (prm->len-- > 1)
				i++;
		}
		if (token[i] && token[i] != '$')
			i++;
	}
	return (token);
}

//!---------------------------
int	ft_var_sz(t_var **var)
{
	int		i;
	t_var	*head;

	if (!var)
		return (-1);
	head = *var;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
//!---------------------------

char *split_tkn(t_token *tkn, t_parms *prm, char *token, int i)
{
	t_var *var;
	t_var *tmp;
	char	*res;

	(void)tkn;
	(void)prm;
	var = NULL;
	while (token[i])
	{
		add_word(&var, token, &i);
		add_quote(&var, token, &i, token[i]);
		// add_var(&var, token, &i);
	}
	tmp = var;
	while (tmp)
	{
		printf("tmp: [%s]\t\ttype: [%c]\n", tmp->wrd, tmp->type);
		tmp = tmp->next;
	}
	tmp = var;
	printf("var size: %d\n", ft_var_sz(&var));
	while (var)
	{
		prm->var = (t_var *)var;
		if (var->type == 'V' || var->type == 'D')
		{
			res = expand_tkn(&var, prm, var->wrd, 0, var->type);
			if (res)
				var->wrd = res;
		}
		var = var->next;
	}
	printf("\n--------------- After expanding ---------------\n");
	// exit(0);
	printf("tmp size: %d\n", ft_var_sz(&tmp));
	while (tmp)
	{
		printf("tmp: [%s]\t\ttype: [%c]\n", tmp->wrd, tmp->type);
		tmp = tmp->next;
	}
	// exit(0);
	return (NULL);
}

void ft_expand(t_token **token, t_parms *prm)
{
	t_token *tkn;
	char *res;

	tkn = *token;
	while (tkn)
	{
		prm->tkn = (t_token *)tkn;
		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<")) && ft_strchr(tkn->token, '$'))
		{
			res = tkn->token;
			res = split_tkn(tkn, prm, res, 0);
			if (res)
				tkn->token = res;
		}
		tkn = tkn->next;
	}
}