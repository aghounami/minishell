/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:47:12 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/19 23:17:17 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem	*lst_new(char *content, int token, int state)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->token = token;
	new->state = state;
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

void	case_single_quote(t_elem **tmp, char *str, t_elem **list)
{
	int	i;

	i = 0;
	while (*tmp)
	{
		if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			if ((*tmp)->state == GENERAL)
			{
				if (i == 0)
				{
					ft_lstadd_back_new_list(list, lst_new(" ", WHITE_SPACE, \
						GENERAL));
					(*tmp) = (*tmp)->next;
					return;
				}
				else
					break ;
			}
			else
				(1) && (str = ft_strjoin(str, (*tmp)->content), \
					(*tmp) = (*tmp)->next);
		}
		else if ((*tmp)->token == QOUTE)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next);
		else if ((*tmp)->token == DOUBLE_QUOTE && i % 2 == 0)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->content[0] == '\0')
			(*tmp) = (*tmp)->next;
		else
			(1) && (str = ft_strjoin(str, (*tmp)->content), \
				(*tmp) = (*tmp)->next);
	}
	ft_lstadd_back_new_list(list, lst_new("\'", QOUTE, GENERAL));
	if (str)
		ft_lstadd_back_new_list(list, lst_new(str, WORD, IN_QUOTE));
	else
		ft_lstadd_back_new_list(list, lst_new("", WORD, IN_QUOTE));
	ft_lstadd_back_new_list(list, lst_new("\'", QOUTE, GENERAL));
	str = NULL;
}

void	case_double_quote(t_elem **tmp, char *str, t_elem **list)
{
	int	i;

	i = 0;
	while (*tmp)
	{
		if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			if ((*tmp)->state == GENERAL)
			{
				if (i == 0)
				{
					ft_lstadd_back_new_list(list, lst_new(" ", WHITE_SPACE, \
						GENERAL));
					(*tmp) = (*tmp)->next;
					return;
				}
				else
					break ;
			}
			else
				(1) && (str = ft_strjoin(str, (*tmp)->content), \
					(*tmp) = (*tmp)->next);
		}
		else if ((*tmp)->token == DOUBLE_QUOTE)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next);
		else if ((*tmp)->token == QOUTE && i % 2 == 0)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->content[0] == '\0')
			(*tmp) = (*tmp)->next;
		else
			(1) && (str = ft_strjoin(str, (*tmp)->content), \
				(*tmp) = (*tmp)->next);
	}
	ft_lstadd_back_new_list(list, lst_new("\"", DOUBLE_QUOTE, GENERAL));
	if (str)
		ft_lstadd_back_new_list(list, lst_new(str, WORD, IN_DQUOTE));
	else
		ft_lstadd_back_new_list(list, lst_new("", WORD, IN_DQUOTE));
	ft_lstadd_back_new_list(list, lst_new("\"", DOUBLE_QUOTE, GENERAL));
	str = NULL;
}
