/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:45:55 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/17 15:33:16 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem	*lstnew(void *content, int token)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (new == NULL)
		return (NULL);
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

t_command	*lstnew_command(t_command **node, int pipe, t_redirection *redir)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	if ((*node)->args[0])
		new->cmd = ft_strdup((*node)->args[0]);
	else
		new->cmd = NULL;
	new->args = ft_strdup_2d((*node)->args);
	new->rdrect = ft_strdup_2d((*node)->rdrect);
	new->pipe = pipe;
	new->redir_in = redir->redir_in;
	new->dredir_out = redir->dredir_out;
	new->here_doc = redir->here_doc;
	new->redir_out = redir->redir_out;
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
