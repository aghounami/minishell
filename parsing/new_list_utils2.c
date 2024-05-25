/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:39:18 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/24 23:52:10 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	next_cnd_special(t_elem **tmp, char **tmp_str, int *k)
{
	if ((*tmp)->content[0] == '\0')
		(*tmp) = (*tmp)->next;
	else if (((*tmp)->token == REDIR_IN \
		|| (*tmp)->token == REDIR_OUT || (*tmp)->token == DREDIR_OUT \
			|| (*tmp)->token == HERE_DOC) && (*tmp)->state == GENERAL)
		return (1);
	else
		(1) && (*tmp_str = ft_join(*tmp_str, (*tmp)->content),
				(*tmp) = (*tmp)->next, *k = 1);
	return (0);
}

int	next_cnd(t_elem **tmp, char **tmp_str)
{
	if ((*tmp)->content[0] == '\0')
		(*tmp) = (*tmp)->next;
	else if (((*tmp)->token == REDIR_IN \
		|| (*tmp)->token == REDIR_OUT || (*tmp)->token == DREDIR_OUT \
			|| (*tmp)->token == HERE_DOC) && (*tmp)->state == GENERAL)
		return (1);
	else
		(1) && (*tmp_str = ft_join(*tmp_str, (*tmp)->content),
				(*tmp) = (*tmp)->next);
	return (0);
}

int	break_case(t_elem **tmp, t_elem **list, char **tmp_str, int k)
{
	if ((*tmp)->state == GENERAL)
	{
		if (k == 0)
		{
			ft_lstadd_back_new_list(list, lst_new(" ", WHITE_SPACE, \
				GENERAL, NO));
			(1) && (free(*tmp_str), (*tmp) = (*tmp)->next);
			return (-1);
		}
		else
			return (1);
	}
	else
		(1) && (*tmp_str = ft_join(*tmp_str, (*tmp)->content),
				(*tmp) = (*tmp)->next);
	return (0);
}
