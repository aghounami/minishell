/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/17 18:09:41 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo_with_quote(t_elem **elem, t_command **command, int *i)
{
	(*elem) = (*elem)->next;
	while ((*elem)->token != '\'')
	{
		(*command)->args[*i] = (*elem)->content;
		*i += 1;
		(*elem) = (*elem)->next;
	}
	(*elem) = (*elem)->next;
}

void echo_with_d_quote(t_elem **elem, t_command **command, int *i)
{
	(*elem) = (*elem)->next;
	while (*elem && (*elem)->token != '\"')
	{
		if ((*elem)->token == ENV)
		{
			char *env = getenv((*elem)->content + 1);
			(*command)->args[*i] = env;
			*i += 1;
		}
		else
		{
			(*command)->args[*i] = (*elem)->content;
			*i += 1;
		}
		(*elem) = (*elem)->next;
	}
	(*elem) = (*elem)->next;
}

void echo_without_quote(t_elem **elem, t_command **command, int *i)
{
	char *tmp;
	
	if ((*elem)->token == WHITE_SPACE)
	{
		tmp = (*elem)->content;
		while ((*elem) && (*elem)->token == WHITE_SPACE)
			(*elem) = (*elem)->next;
		if ((*elem))
		{
			(*command)->args[*i] = tmp;
			*i += 1;
		}
	}
	else if ((*elem)->token == ESCAPE)
	{
		(*command)->args[*i] = &(*elem)->content[1];
		*i += 1;
		(*elem) = (*elem)->next;
	}
	else
	{
		if ((*elem)->token == ENV)
		{
			char *env = getenv((*elem)->content + 1);
			(*command)->args[*i] = env;
			*i += 1;
		}
		else
		{
			(*command)->args[*i] = (*elem)->content;
			*i += 1;
		}
		(*elem) = (*elem)->next;
	}
}

void command_comand(t_elem **elem, t_command **command)
{
	if ((*elem)->token == QOUTE || (*elem)->token == DOUBLE_QUOTE)
	{
		(*elem) = (*elem)->next;
		while ((*elem)->token != DOUBLE_QUOTE && (*elem)->token != QOUTE)
		{
			if ((*elem)->token == ENV)
			{
				char *env = getenv((*elem)->content + 1);
				(*command)->cmd = ft_strjoin((*command)->cmd, env);
			}
			else
				(*command)->cmd = ft_strjoin((*command)->cmd, (*elem)->content);
			(*elem) = (*elem)->next;
		}
		*elem = (*elem)->next;
	}
	else
	{
		if ((*elem)->token == ENV)
		{
			char *env = getenv((*elem)->content + 1);
			(*command)->cmd = env;
		}
		else
			(*command)->cmd = (*elem)->content;
		(*elem) = (*elem)->next;
	}
}

void stack_command(t_elem *elem, t_command **command)
{
	int i;

	i = 0;
	while (elem->token == WHITE_SPACE)
		elem = elem->next;
	while (elem)
	{
		command_comand(&elem, command);
		(*command)->args[i] = (*command)->cmd;
		i++;
		while (elem && elem->token != PIPE_LINE)
		{
			
			if (elem->token == QOUTE)
				echo_with_quote(&elem, command, &i);
			else if (elem->token == DOUBLE_QUOTE)
				echo_with_d_quote(&elem, command, &i);
			else
				echo_without_quote(&elem, command, &i);
		}
	}
	(*command)->args[i] = NULL;
}
