/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:45:55 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/14 15:53:40 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntax_error(t_elem **elem)
{
	t_elem *tmp;
	// t_elem *tmp2;

	tmp = *elem;
	int error = 0;
	while (tmp)
	{
		// if (tmp->token == PIPE_LINE || tmp->token == REDIR_IN || tmp->token == REDIR_OUT || tmp->token == HERE_DOC || tmp->token == DREDIR_OUT)
		// {
		// 	tmp2 = tmp->next;
		// 	while (tmp2 && tmp2->token == WHITE_SPACE)
		// 		tmp2 = tmp2->next;
		// 	if (!tmp2 || tmp2->token == PIPE_LINE)
		// 	{
		// 		error = 1;
		// 		break;
		// 	}
		// }
		// error = (tmp->token == REDIR_IN && tmp->next->token == REDIR_OUT);
		// error = (tmp->token == REDIR_OUT && tmp->next->token == REDIR_IN);
		// error = (tmp->token == HERE_DOC && tmp->next->token == DREDIR_OUT);
		// error = (tmp->token == DREDIR_OUT && tmp->next->token == HERE_DOC);
		// error = (tmp->token == REDIR_IN && tmp->next->token == DREDIR_OUT);
		// error = (tmp->token == REDIR_OUT && tmp->next->token == REDIR_IN);
		// if (error)
		// 	break;
		// else if (tmp->token == ESCAPE && tmp->content[1] == '\0')
		// {
		// 	tmp2 = tmp->next;
		// 	while (tmp2 && tmp2->token == SPACE)
		// 		tmp2 = tmp2->next;
		// 	if (!tmp2)
		// 	{
		// 		error = 1;
		// 		break;
		// 	}
		// }
		if (tmp->token == DOUBLE_QUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token != DOUBLE_QUOTE)
				tmp = tmp->next;
			if (!tmp)
			{
				printf("syntax erkkkror\n");
				error = 1;
				break;
			}
			// tmp = tmp->next;
		}
		// else if (tmp->token == QOUTE)
		// {
		// 	tmp2 = tmp->next;
		// 	while (tmp2 && tmp2->token != QOUTE)
		// 		tmp2 = tmp2->next;
		// 	if (!tmp2)
		// 	{
		// 		error = 1;
		// 		break;
		// 	}
		// }
		tmp = tmp->next;
	}
	if (error)
	{
		// printf("syntax error\n");
		return;
	}
}
// syntax error in \\ and echo "\n" \n

t_elem *lstnew(void *content, int token)
{
	t_elem *new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_elem *lstlast(t_elem *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void lstadd_back(t_elem **lst, t_elem *new)
{
	t_elem *last;

	if (!lst || !new)
		return;
	last = lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}
