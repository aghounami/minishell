/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/21 00:39:53 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void with_quote(t_elem **elem, t_command **command, int *i)
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

void with_d_quote(t_elem **elem, t_command **command, int *i)
{
	(*elem) = (*elem)->next;
	while (*elem && (*elem)->token != '\"')
	{
		if ((*elem)->token == ENV)
		{
			char *env = getenv((*elem)->content + 1);
			if (env)
			{
				(*command)->args[*i] = env;
				*i += 1;
			}
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

void without_quote(t_elem **elem, t_command **command, int *i)
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
		if ((*elem)->token == ENV && (*elem)->content[1] != '\0')
		{
			char *env = getenv((*elem)->content + 1);
			if (env)
			{
				(*command)->args[*i] = env;
				*i += 1;
			}
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
				if (env)
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
			if (env)
				(*command)->cmd = env;
		}
		else
			(*command)->cmd = (*elem)->content;
		(*elem) = (*elem)->next;
	}
}

void stack_command(t_elem *elem, t_command **command, int *i)
{
	while (elem->token == WHITE_SPACE)
		elem = elem->next;
	while (elem)
	{
		command_comand(&elem, command);
		(*command)->args[*i] = (*command)->cmd;
		*i += 1;
		while (elem && elem->token != PIPE_LINE)
		{
			
			if (elem->token == QOUTE)
				with_quote(&elem, command, i);
			else if (elem->token == DOUBLE_QUOTE)
				with_d_quote(&elem, command, i);
			else
				without_quote(&elem, command, i);
		}
	}
	(*command)->args[*i] = NULL;
}
