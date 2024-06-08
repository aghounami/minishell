/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:47:12 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/07 16:57:37 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	utils_special_case(t_elem **tmp, char **tmp_str, t_entier *ent)
{
	if ((*tmp)->token == QOUTE && ent->i != 0 && ent->n == 1)
		(1) && ((*tmp) = (*tmp)->next, ent->i = 0);
	else if ((*tmp)->token == DOUBLE_QUOTE && ent->i != 0 && ent->n == 2)
		(1) && ((*tmp) = (*tmp)->next, ent->i = 0);
	else
		if (next_cnd_special(tmp, tmp_str, &ent->k))
			return (1);
	return (0);
}

void	special_case(t_elem **tmp, t_elem **list, char	*tmp_str)
{
	t_entier	*ent;

	ent = malloc(sizeof(t_entier));
	(1) && (ent->i = 0, ent->j = 0, ent->k = 0, ent->n = 0);
	while (*tmp)
	{
		if ((*tmp)->token == QOUTE && ent->i == 0)
			(1) && (ent->i = ent->i + 1, (*tmp) = (*tmp)->next, ent->n = 1);
		else if ((*tmp)->token == DOUBLE_QUOTE && ent->i == 0)
			(1) && (ent->i = ent->i + 1, (*tmp) = (*tmp)->next, ent->n = 2);
		else if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			ent->j = break_case(tmp, list, &tmp_str, ent->k);
			if (ent->j == 1)
				break ;
			else if (ent->j == -1)
				return (free(ent));
		}
		else
			if (utils_special_case(tmp, &tmp_str, ent))
				break ;
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_DQUOTE, NO));
	(1) && (free(tmp_str), free(ent), tmp_str = NULL);
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
