/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:45:55 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/07 13:31:03 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem *lstnew(void *content, int token , char *var_name)
{
	t_elem *new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token = token;
	if (token == ENV)
		new->flag_env = YES;
	else
		new->flag_env = NO;
	new->env_var = ft_strdup(var_name);
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

char **ft_strdup_2d(char **str)
{
	int i;
	char **new;

	i = 0;
	if (str == NULL)
		return NULL;
	while (str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		// free (str[i]);
		i++;
	}
	new[i] = NULL;
	// free(str);
	return (new);
}

t_command *lstnew_command(t_command **node, int pipe, t_redirection *redir)
{
	t_command *new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup((*node)->cmd);
	new->args = ft_strdup_2d((*node)->args);
	new->rd_in = ft_strdup_2d((*node)->rd_in);
	new->rd_out = ft_strdup_2d((*node)->rd_out);
	new->pipe = pipe;
	new->redir_in = redir->redir_in;
	new->dredir_out = redir->dredir_out;
	new->here_doc = redir->here_doc;
	new->redir_out = redir->redir_out;
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
