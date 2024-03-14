/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:09:08 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/14 14:40:29 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	state(t_elem **elem)
{
	t_elem	*tmp;
	int		flag_quote;
	int		flag_d_quote;
	t_elem	*prev;

	(1) && (flag_quote = 1, flag_d_quote = 1, tmp = *elem, prev = NULL);
	while (tmp)
	{
		if (prev && prev->token == DOUBLE_QUOTE && tmp->token != DOUBLE_QUOTE && flag_d_quote % 2 == 0)
			case_1(&tmp);
		else if (prev && prev->token == QOUTE && tmp->token != QOUTE && flag_quote % 2 == 0)
			case_2(&tmp);
		else
		{
			tmp->state = GENERAL;
			prev = tmp;
			if (prev->token == DOUBLE_QUOTE)
				flag_d_quote++;
			if (prev->token == QOUTE)
				flag_quote++;
			tmp = tmp->next;
		}
	}
}
