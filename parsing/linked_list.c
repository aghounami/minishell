/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:45:55 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/02 19:26:09 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem	*lstnew(void *content, int token)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (new == NULL)
		malloc_fail();
	new->content = content;
	new->token = token;
	if (token == ENV)
		new->flag_env = YES;
	else
		new->flag_env = NO;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_elem	*lstlast(t_elem *lst)
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
	new->prev = last;
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

t_command	*lstnew_command(t_command **node, int pipe)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		malloc_fail();
	if ((*node)->args[0])
		new->cmd = ft_strdup((*node)->args[0]);
	else
		new->cmd = NULL;
	new->args = ft_strdup_2d((*node)->args);
	new->rdrect = ft_strdup_2d((*node)->rdrect);
	new->pipe = pipe;
	new->check_expand = (*node)->check_expand;
	new->next = NULL;
	return (new);
}

void	lstadd_back_command(t_command **lst, t_command *new)
{
	t_command	*last;

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
