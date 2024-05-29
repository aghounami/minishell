/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:11:29 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/29 16:34:47 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem	*new_list_new(char *content, t_elem *tmp)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->token = tmp->token;
	new->flag_env = tmp->flag_env;
	new->state = tmp->state;
	new->expand = 0;
	new->next = NULL;
	return (new);
}

void	next_condition(t_elem **tmp, t_elem **list, char *str)
{
	if ((*tmp) && ((*tmp)->token == WORD || (*tmp)->token == NEW_WORD) \
		&& (*tmp)->next && ((*tmp)->next->token == BACK_SLASH \
			|| (*tmp)->next->token == NEW_WORD || (*tmp)->next->token == WORD) \
				&& (*tmp)->token != QOUTE && (*tmp)->token != DOUBLE_QUOTE)
		special_case(tmp, list, 0, ft_strdup(""));
	else if (((*tmp) && (*tmp)->token != QOUTE \
		&& (*tmp)->token != DOUBLE_QUOTE) \
			&& (((*tmp)->next && ((*tmp)->next->token != QOUTE \
				&& (*tmp)->next->token != DOUBLE_QUOTE)) || !(*tmp)->next))
	{
		str = ft_strdup((*tmp)->content);
		ft_lstadd_back_new_list(list, new_list_new(str, (*tmp)));
		(1) && (free(str), str = NULL, (*tmp) = (*tmp)->next);
	}
	else if ((*tmp) && ((*tmp)->token == QOUTE \
		|| ((*tmp)->next && (*tmp)->next->token == QOUTE \
			&& (*tmp)->next->state == GENERAL)))
		case_single_quote(tmp, list);
	else if ((*tmp) && ((*tmp)->token == DOUBLE_QUOTE \
		|| ((*tmp)->next && (*tmp)->next->token == DOUBLE_QUOTE \
			&& (*tmp)->next->state == GENERAL)))
		case_double_quote(tmp, list);
}

void	all_condition(char *str, t_elem *tmp, t_elem **list)
{
	while (tmp)
	{
		if (tmp && (tmp->token == REDIR_IN || tmp->token == REDIR_OUT \
			|| tmp->token == DREDIR_OUT || tmp->token == HERE_DOC))
		{
			str = ft_strdup(tmp->content);
			ft_lstadd_back_new_list(list, new_list_new(str, tmp));
			(1) && (free(str), str = NULL, tmp = tmp->next);
		}
		else if (tmp && tmp->token == WHITE_SPACE)
		{
			str = ft_strdup(tmp->content);
			ft_lstadd_back_new_list(list, new_list_new(str, tmp));
			(1) && (free(str), str = NULL, tmp = tmp->next);
		}
		else
			next_condition(&tmp, list, str);
	}
}

void	new_linked_list(t_elem **pars, t_elem **list)
{
	t_elem	*tmp;
	char	*str;

	str = NULL;
	tmp = *pars;
	while (tmp && tmp->token == WHITE_SPACE)
		tmp = tmp->next;
	all_condition(str, tmp, list);
	ft_free_lexer(pars);
}
