/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/24 21:55:27 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_elem **elem, t_command **command, int *i, char **env)
{
	int index = 0;
	int j = 0;
	
	char *env_name = malloc(sizeof(char) * 100);
	char *env_value = malloc(sizeof(char) * 100);
	env_name = ft_strdup((*elem)->content + 1);
	while (env[index])
	{
		if (ft_strncmp(env[index], env_name, ft_strlen(env_name)) == 0 && env[index][ft_strlen(env_name)] == '=')
		{
			while (env[index][j] != '=')
				j++;
			env_value = ft_strdup(env[index] + j + 1);
			(*command)->args[*i] = env_value;
			*i += 1;
			break ;
		}
		index++;
	}
}

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

void with_d_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	(*elem) = (*elem)->next;
	while (*elem && (*elem)->token != '\"')
	{
		if ((*elem)->token == ENV)
			get_env(elem, command, i, env);
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

	if ((*elem)->token == WHITE_SPACE && strncmp((*command)->cmd, "echo", 4) == 0)
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
			get_env(elem, command, i, NULL);
		else if ((*elem)->token != WHITE_SPACE)
		{
			(*command)->args[*i] = (*elem)->content;
			*i += 1;
		}
		(*elem) = (*elem)->next;
	}
}

void command_comand(t_elem **elem, t_command **command , char **env)
{
	(void)env;
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

void stack_command(t_elem *elem, t_command **command, int *i, char **env)
{
	while (elem->token == WHITE_SPACE)
		elem = elem->next;
	while (elem)
	{
		command_comand(&elem, command, env);
		(*command)->args[*i] = (*command)->cmd;
		*i += 1;
		while (elem && elem->token != PIPE_LINE)
		{
			if (elem->token == QOUTE)
				with_quote(&elem, command, i);
			else if (elem->token == DOUBLE_QUOTE)
				with_d_quote(&elem, command, i, env);
			else
				without_quote(&elem, command, i);
		}
	}
	(*command)->args[*i] = NULL;
}
