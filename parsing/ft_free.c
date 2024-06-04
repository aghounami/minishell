/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:08:57 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/02 19:25:26 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_lexer(t_elem **pars)
{
	t_elem	*tmp2;

	while (*pars)
	{
		tmp2 = (*pars)->next;
		free((*pars)->content);
		free(*pars);
		*pars = tmp2;
	}
}

void	ft_free_command(t_command **command)
{
	t_command	*tmp;
	int			i;

	while (*command)
	{
		tmp = (*command)->next;
		if ((*command)->cmd)
			free((*command)->cmd);
		i = 0;
		while ((*command)->args[i])
		{
			free((*command)->args[i]);
			i++;
		}
		free((*command)->args);
		i = 0;
		while ((*command)->rdrect[i])
		{
			free((*command)->rdrect[i]);
			i++;
		}
		free((*command)->rdrect);
		free(*command);
		*command = tmp;
	}
}

int	count_worlds(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			count++;
		i++;
	}
	return (count + 1);
}

t_elem	*lst_new(char *content, int token, int state, int flag_env)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		malloc_fail();
	new->content = ft_strdup(content);
	new->token = token;
	new->flag_env = flag_env;
	new->state = state;
	new->expand = 1;
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
