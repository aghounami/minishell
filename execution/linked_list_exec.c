/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:29:42 by hel-magh          #+#    #+#             */
/*   Updated: 2024/04/02 17:57:02 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_env	*ft_lstnew_exec(char *value, char *variable)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->variable = variable;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_exec(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast_exec(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

t_env	*ft_lstlast_exec(t_env *lst)
{
	if (lst)
	{
		while (lst)
		{
			if (!lst->next)
				return (lst);
			lst = lst->next;
		}
	}
	return (lst);
}

void	ft_lstdelone_exec(t_env *lst)
{
	
	if (lst)
	{
		free(lst);
	}
}
