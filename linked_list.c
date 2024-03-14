/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:45:55 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/14 02:38:18 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntax_error(t_elem **elem)
{
	t_elem *tmp;

	tmp = *elem;
	int error = 0;
	while (tmp)
	{
		error = (tmp->token == PIPE_LINE && tmp->next && tmp->next->token == PIPE_LINE);
		error = (tmp->token == PIPE_LINE && tmp->next && tmp->next->token == PIPE_LINE);
		error = (tmp->token == REDIR_IN && tmp->next && tmp->next->token == REDIR_IN);
		error = (tmp->token == REDIR_OUT && tmp->next && tmp->next->token == REDIR_OUT && tmp->next->next && tmp->next->next->token == REDIR_OUT);
		error = (tmp->token == REDIR_IN && tmp->next && tmp->next->token == REDIR_IN && tmp->next->next && tmp->next->next->token == REDIR_IN);
		error = (tmp->token == REDIR_OUT && tmp->next && tmp->next->token == REDIR_IN);
		error = (tmp->token == REDIR_IN && tmp->next && tmp->next->token == REDIR_OUT);
		if (tmp->token == ESCAPE)
		{
			if (tmp->content[1] != '\\')
			{
				error = 1;
				break;
			}
		}
		if (tmp->token == PIPE_LINE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token == WHITE_SPACE)
				tmp = tmp->next;
			if (!tmp)
			{
				error = 1;
				break;
			}
		}
		if (error)
			break;
		if (tmp->token == DOUBLE_QUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token != DOUBLE_QUOTE)
				tmp = tmp->next;
			if (!tmp)
			{
				error = 1;
				break;
			}
		}
		if (tmp->token == QOUTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token != QOUTE)
				tmp = tmp->next;
			if (!tmp)
			{
				error = 1;
				break;
			}
		}
		tmp = tmp->next;
	}
	if (error)
	{
		printf("syntax error\n");
		return ;
	}
}
// syntax error in \\ and echo "\n" \n

t_elem	*lstnew(void *content, int token)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_elem    *lstlast(t_elem *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void	lstadd_back(t_elem **lst, t_elem *new)
{
	t_elem	*last;

	if (!lst || !new)
		return ;
	last = lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}
