// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   norm.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/15 18:29:54 by aaghla            #+#    #+#             */
// /*   Updated: 2024/05/20 11:23:36 by aaghla           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "parsing.h"

// int	check_splt(t_token *tkn)
// {
// 	t_token	*prv;

// 	prv = tkn;
// 	while (prv && prv->prev)
// 	{
// 		if (!prv->prev || prv->prev->type == '|')
// 			break ;
// 		prv = prv->prev;
// 	}
// 	while (prv && prv != tkn)
// 	{
// 		if (prv->type == '<' || prv->type == '>')
// 			prv = prv->next->next;
// 		else
// 		{
// 			if (!ft_strcmp(prv->token, "export"))
// 				return (1);
// 			else
// 				return (0);
// 		}
// 	}
// 	return (0);
// }

// void	add_word(t_var **var, char *token, int *i)
// {
// 	char	tmp;
// 	int		j;

// 	j = *i;
// 	if (!token[j] || token[j] == '"' || token[j] == '\'')
// 		return ;
// 	while (token[*i] && token[*i] != '\'' && token[*i] != '"')
// 		(*i)++;
// 	tmp = token[*i];
// 	token[*i] = '\0';
// 	if (token[j] && ft_strchr(token + j, '$'))
// 		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'V'));
// 	else if (token[j])
// 		ft_var_addb(var, ft_var_new(my_strdup(token + j), 'W'));
// 	token[*i] = tmp;
// }

// void	add_quote(t_var **var, char *token, int *i, char c)
// {
// 	char	*tmp_s;
// 	char	tmp_c;
// 	int		j;

// 	tmp_s = token;
// 	j = *i;
// 	if (c != '\'' && c != '"')
// 		return ;
// 	(*i)++;
// 	while (token[*i] && token[*i] != c)
// 		(*i)++;
// 	(*i)++;
// 	tmp_c = token[*i];
// 	token[*i] = '\0';
// 	token = ft_strtrim(token + j, &c);
// 	if (token[0] && token[0] != '\'' && ft_strchr(token, '$'))
// 		ft_var_addb(var, ft_var_new(my_strdup(token), 'D'));
// 	else if (token[0])
// 		ft_var_addb(var, ft_var_new(my_strdup(token), 'Q'));
// 	tmp_s[*i] = tmp_c;
// }

// char	*splt_var(t_parms *prm, char *var, char *bef, char *aft)
// {
// 	char	**arr;
// 	t_var	*var_t;
// 	int		i;

// 	var_t = (t_var *)prm->var;
// 	arr = my_split(var, ' ');
// 	i = 0;
// 	var_t->wrd = ft_pstrjoin(bef, arr[i]);
// 	var_t->type = 'N';
// 	prm->v_len = 0;
// 	while (arr[++i +1])
// 	{
// 		prm->v_len++;
// 		ft_var_insrt(&var_t, ft_var_new(arr[i], 'N'));
// 		var_t = var_t->next;
// 	}
// 	prm->l_len = ft_len(arr[i]);
// 	aft = ft_pstrjoin(arr[i], aft);
// 	ft_var_insrt(&var_t, ft_var_new(aft, 'L'));
// 	return (NULL);
// }

// char	*expand_it(char *wd, t_parms *prm, int i)
// {
// 	char	*var;
// 	char	*res;
// 	int		j;

// 	j = i + 1;
// 	var = ft_trim(wd, i + 1);
// 	res = check_vlid_var(prm, wd, i);
// 	if (res)
// 		return (res);
// 	while (wd[j] && ((wd[j] == '_' || (wd[j] >= 'a' && wd[j] <= 'z'))
// 			|| (wd[j] >= 'A' && wd[j] <= 'Z')
// 			|| (wd[j] >= '0' && wd[j] <= '9')))
// 		j++;
// 	var = ft_env_srch(var, &prm->env);
// 	if (var && (prm->c == 'V' || prm->c == 'N' || prm->c == 'L')
// 		&& (ft_strchr(var, ' ') || ft_strchr(var, '\t'))
// 		&& !check_splt(prm->tkn))
// 		return (splt_var(prm, var, get_prev(wd, i), wd + j));
// 	if (var)
// 	{
// 		prm->len = ft_len(var);
// 		return (ft_pstrjoin(var, wd + j));
// 	}
// 	return (wd + j);
// }

// char	*expand_quot(t_var **var_t, t_parms *prm, char *token, char *res)
// {
// 	int	i;

// 	i = 0;
// 	if ((*var_t)->type == 'L')
// 		while (prm->l_len-- > 0)
// 			i++;
// 	while (token[i])
// 	{
// 		if (token[i] == '$')
// 		{
// 			prm->len = 0;
// 			res = expand_it(token, prm, i);
// 			if (!res)
// 				return (NULL);
// 			token = ft_pstrjoin(get_prev(token, i), res);
// 			while (prm->len-- > 0)
// 				i++;
// 		}
// 		if (token[i] && token[i] != '$')
// 			i++;
// 	}
// 	return (token);
// }

// void	join_vars(t_token **tkn, t_var **var, t_parms *prm, int *flag)
// {
// 	char	*res;

// 	res = "";
// 	while ((*var) && (*var)->type != 'N')
// 	{
// 		res = ft_pstrjoin(res, (*var)->wrd);
// 		*var = (*var)->next;
// 	}
// 	if (*var && (*var)->type == 'N')
// 	{
// 		res = ft_pstrjoin(res, (*var)->wrd);
// 		*var = (*var)->next;
// 	}
// 	if (*flag)
// 	{
// 		ft_token_addb(tkn, ft_token_new(res, 'V', 0));
// 		prm->t_len++;
// 	}
// 	else
// 	{
// 		(*tkn)->token = res;
// 		prm->t_len++;
// 		*flag = 1;
// 	}
// }

// void	add_vars(t_token **tkn, t_parms *prm, t_var *var)
// {
// 	char	*res;
// 	int		flag;

// 	flag = 0;
// 	res = "";
// 	prm->t_len = 0;
// 	while (var)
// 	{
// 		join_vars(tkn, &var, prm, &flag);
// 		while (var && var->type == 'N')
// 		{
// 			ft_token_addb(tkn, ft_token_new(var->wrd, 'V', 0));
// 			prm->t_len++;
// 			var = var->next;
// 			flag = 1;
// 		}
// 	}
// }

// void	split_tkn(t_parms *prm, t_var *var, char *token, int i)
// {
// 	char	*res;
// 	t_var	*tmp;

// 	while (token[i])
// 	{
// 		add_word(&var, token, &i);
// 		add_quote(&var, token, &i, token[i]);
// 	}
// 	prm->var = var;
// 	tmp = var;
// 	printf("\n\n--------------- var after expanding ---------------");
// 	while (tmp)
// 	{
// 		printf("tmp wrd: [%s]\t\ttype: [%c]\n", tmp->wrd, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	printf("---------------------------------------------------");
// 	while (var)
// 	{
// 		prm->var = (t_var *)var;
// 		if (var->type == 'V' || var->type == 'D'
// 			|| var->type == 'N' || var->type == 'L')
// 		{
// 			prm->c = var->type;
// 			res = expand_quot(&var, prm, var->wrd, "");
// 			if (res)
// 				var->wrd = res;
// 			while(prm->v_len-- > 1)
// 				var = var->next;
// 		}
// 		var = var->next;
// 	}
// }

// void ft_expand(t_token *token, t_parms *prm)
// {
// 	t_token *tkn;
// 	char *res;

// 	tkn = token;
// 	while (tkn)
// 	{
// 		prm->tkn = (t_token *)tkn;
// 		if ((!tkn->prev || ft_strcmp(tkn->prev->token, "<<")))
// 		{
// 			res = tkn->token;
// 			split_tkn(prm, NULL, res, 0);
// 			add_vars(&tkn, prm, (t_var*)prm->var);
// 			while ( prm->t_len-- > 1)
// 			{
// 				tkn = tkn->next;
// 			}
// 		}
// 		if (tkn)
// 		tkn = tkn->next;
// 	}
// }
