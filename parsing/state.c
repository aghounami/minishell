/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:09:08 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/25 18:09:33 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_1(t_elem **tmp)
{
	while (*tmp && (*tmp)->token != DOUBLE_QUOTE)
	{
		(*tmp)->state = IN_DQUOTE;
		*tmp = (*tmp)->next;
	}
}

void	case_2(t_elem **tmp)
{
	while ((*tmp) && (*tmp)->token != QOUTE)
	{
		(*tmp)->state = IN_QUOTE;
		(*tmp) = (*tmp)->next;
	}
}

void	state(t_elem **elem, char **env, int flag)
{
	t_elem	*tmp;
	int		flag_quote;
	int		flag_d_quote;
	t_elem	*prev;

	(1) && (flag_quote = 1, flag_d_quote = 1, tmp = *elem, prev = NULL);
	while (tmp)
	{
		if (prev && prev->token == DOUBLE_QUOTE \
			&& tmp->token != DOUBLE_QUOTE && flag_d_quote % 2 == 0)
			case_1(&tmp);
		else if (prev && prev->token == QOUTE \
			&& tmp->token != QOUTE && flag_quote % 2 == 0)
		{
			if (flag == 1)
				case_1(&tmp);
			else
				case_2(&tmp);
		}
		else
		{
			(1) && (tmp->state = GENERAL, prev = tmp);
			if (prev->token == DOUBLE_QUOTE)
				flag_d_quote++;
			if (prev->token == QOUTE)
				flag_quote++;
			tmp = tmp->next;
		}
	}
	stack_env(*elem, env);
}

t_elem	*lst_new(char *content, int token, int state, int flag_env)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->token = token;
	new->flag_env = flag_env;
	new->state = state;
	new->expand = 1;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_new_list(t_elem **lst, t_elem *new)
{
	t_elem	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
