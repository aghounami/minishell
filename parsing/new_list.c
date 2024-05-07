/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:11:29 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/07 13:39:44 by aghounam         ###   ########.fr       */
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
	new->env_var = ft_strdup(tmp->env_var);
	new->state = tmp->state;
	new->next = NULL;
	return (new);
}

void	all_condition(char *str, t_elem *tmp, t_elem **list)
{
	while (tmp)
	{
		if ((tmp->token != QOUTE && tmp->token != DOUBLE_QUOTE) \
			&& ((tmp->next && (tmp->next->token != QOUTE \
				&& tmp->next->token != DOUBLE_QUOTE)) || !tmp->next))
		{
			str = ft_strdup(tmp->content);
			ft_lstadd_back_new_list(list, new_list_new(str, tmp));
			str = NULL;
			tmp = tmp->next;
		}
		else if (tmp->token == WHITE_SPACE)
		{
			str = ft_strdup(tmp->content);
			ft_lstadd_back_new_list(list, new_list_new(str, tmp));
			str = NULL;
			tmp = tmp->next;
		}
		else if (tmp->token == QOUTE || (tmp->next && tmp->next->token == QOUTE \
			&& tmp->next->state == GENERAL))
			case_single_quote(&tmp, str, list);
		else if (tmp->token == DOUBLE_QUOTE || (tmp->next \
			&& tmp->next->token == DOUBLE_QUOTE && tmp->next->state == GENERAL))
			case_double_quote(&tmp, str, list);
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
