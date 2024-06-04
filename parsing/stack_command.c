/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/02 19:26:37 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize(t_elem *elem)
{
	int		i;
	t_elem	*tmp;

	i = 0;
	tmp = elem;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	param_init(t_command **new, t_elem **elem, t_cmd_utils **utils)
{
	int		len;
	t_elem	*tmp;

	(1) && ((*utils)->i = 0, (*utils)->index = 0, len = 0);
	tmp = *elem;
	while (tmp)
	{
		if (tmp->token == REDIR_OUT || tmp->token == DREDIR_OUT \
			|| tmp->token == HERE_DOC || tmp->token == REDIR_IN)
			len++;
		tmp = tmp->next;
	}
	*new = malloc(sizeof(t_command));
	(*new)->args = malloc(sizeof(char *) * ((lstsize(*elem)) + 1));
	(*new)->rdrect = malloc(sizeof(char *) * ((len * 2) + 1));
	if (!(*new) || !(*new)->args || !(*new)->rdrect)
		malloc_fail();
	(*new)->pipe = 0;
	(*new)->redir_in = 0;
	(*new)->redir_out = 0;
	(*new)->dredir_out = 0;
	(*new)->here_doc = 0;
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
}

void	command_add_back(t_command **command, t_command **new, char **env, \
	t_cmd_utils *utils)
{
	int				pipe;

	pipe = 0;
	(1) && ((*new)->evr = env, (*new)->args[utils->i] = NULL, \
		(*new)->rdrect[utils->index] = NULL);
	if ((*new) && (*new)->pipe == 1)
		pipe = 1;
	lstadd_back_command(command, \
	lstnew_command(new, pipe));
	ft_free_2d((*new)->args);
	ft_free_2d((*new)->rdrect);
	(free((*new)), (*new) = NULL);
}

void	stack_command(t_elem *elem, t_command **command, char **env)
{
	t_cmd_utils	*utils;
	t_command	*new;

	utils = malloc(sizeof(t_cmd_utils));
	if (!utils)
		malloc_fail();
	while (elem)
	{
		param_init(&new, &elem, &utils);
		while (elem && elem->token != PIPE_LINE)
			without_quote(&elem, &new, &utils);
		if ((elem) && (elem)->token == PIPE_LINE)
			(1) && (new->pipe = 1, (elem) = (elem)->next);
		command_add_back(command, &new, env, utils);
	}
	free (utils);
}
