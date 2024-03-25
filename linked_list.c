/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:45:55 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/25 17:22:27 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem *lstnew(void *content, int token , t_elem **prev)
{
	t_elem *new;

	(void)prev;
	new = (t_elem *)malloc(sizeof(t_elem));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
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
	new->prev = last;
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

t_command *lstnew_command(char **agrs, char *cmd)
{
	t_command *new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->args = agrs;
	new->next = NULL;
	return (new);
}

void lstadd_back_command(t_command **lst, t_command *new)
{
	t_command *last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
