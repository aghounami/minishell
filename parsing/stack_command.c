/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/04 02:55:40 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	param_init(t_command **new, int *i, t_elem **elem)
{
	*i = 0;
	*new = malloc(sizeof(t_command));
	(*new)->args = malloc(sizeof(char *) * 100);
	(*new)->pipe = 0;
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
}

void	command_add_back(t_command **command, t_command **new, int i, char **env)
{
	int pipe;

	pipe = 0;
	if (i > 0)
	{
		(1) && ((*new)->evr = env, (*new)->args[i] = NULL);
		if ((*new)->pipe == 1)
			pipe = 1;
		lstadd_back_command(command, \
		lstnew_command((*new)->args, (*new)->cmd, pipe));
		ft_free_2d((*new)->args);
		free((*new)->cmd);
		free((*new));
		(*new) = NULL;
	}
}

void	stack_command(t_elem *elem, t_command **command, char **env)
{
	int			i;
	t_command	*new;

	while (elem)
	{
		param_init(&new, &i, &elem);
		while (elem && elem->token != PIPE_LINE)
		{
			if (elem->token == QOUTE)
				with_quote(&elem, &new, &i);
			else if (elem->token == DOUBLE_QUOTE)
				with_d_quote(&elem, &new, &i, env);
			else
				without_quote(&elem, &new, &i, env);
			if (i > 0)
				new->cmd = ft_strdup(new->args[0]);
			else
				new->cmd = NULL;
		}
		if ((elem) && (elem)->token == PIPE_LINE)
			(1) && (new->pipe = 1, (elem) = (elem)->next);
		command_add_back(command, &new, i, env);
	}
}
