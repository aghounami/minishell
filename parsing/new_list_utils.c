/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:47:12 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/25 19:39:16 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	special_case(t_elem **tmp, t_elem **list, int n)
{
	printf("special case\n");
	int		j;
	int		i;
	int		k;
	char	*tmp_str;

	(1) && (k = 0, i = 0, tmp_str = ft_strdup(""));
	while (*tmp)
	{
		if ((*tmp)->token == QOUTE && i == 0)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next, n = 1);
		else if ((*tmp)->token == DOUBLE_QUOTE && i == 0)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next, n = 2);
		else if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			j = break_case(tmp, list, &tmp_str, k);
			if (j == 1)
				break ;
			else if (j == -1)
				return ;
		}
		else if ((*tmp)->token == QOUTE && i != 0 && n == 1)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->token == DOUBLE_QUOTE && i != 0 && n == 2)
			(*tmp) = (*tmp)->next;
		else
			if (next_cnd_special(tmp, &tmp_str, &k))
				break ;
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_QUOTE, NO));
	free(tmp_str);
}

void	case_single_quote(t_elem **tmp, t_elem **list)
{
	int		i;
	int		j;
	char	*tmp_str;

	(1) && (tmp_str = ft_strdup(""), i = 0);
	while (*tmp)
	{
		if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			j = break_case(tmp, list, &tmp_str, i);
			if (j == 1)
				break ;
			else if (j == -1)
				return ;
		}
		else if ((*tmp)->token == QOUTE)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next);
		else if ((*tmp)->token == DOUBLE_QUOTE && i % 2 == 0)
			(*tmp) = (*tmp)->next;
		else
			if (next_cnd(tmp, &tmp_str))
				break ;
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_QUOTE, NO));
	free(tmp_str);
}

void	case_double_quote(t_elem **tmp, t_elem **list)
{
	int		j;
	int		i;
	char	*tmp_str;

	(1) && (tmp_str = ft_strdup(""), i = 0);
	while (*tmp)
	{
		if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			j = break_case(tmp, list, &tmp_str, i);
			if (j == 1)
				break ;
			else if (j == -1)
				return ;
		}
		else if ((*tmp)->token == DOUBLE_QUOTE)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next);
		else if ((*tmp)->token == QOUTE && i % 2 == 0)
			(*tmp) = (*tmp)->next;
		else
			if (next_cnd(tmp, &tmp_str))
				break ;
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_DQUOTE, NO));
	free(tmp_str);
}
