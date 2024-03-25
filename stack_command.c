/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/25 00:14:03 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_elem **elem, char **env)
{
	int index = 0;
	int j = 0;
	
	char *env_name = malloc(sizeof(char) * 100);
	char *env_value = malloc(sizeof(char) * 100);
	env_name = ft_strdup((*elem)->content + 1);
	env_value = NULL;
	while (env[index])
	{
		if (ft_strncmp(env[index], env_name, ft_strlen(env_name)) == 0 && env[index][ft_strlen(env_name)] == '=')
		{
			while (env[index][j] != '=')
				j++;
			env_value = ft_strdup(env[index] + j + 1);
			break ;
		}
		index++;
	}
	return (env_value);
}

void with_quote(t_elem **elem, t_command **command, int *i)
{
	char *str = malloc(sizeof(char) * 100);
	str = ""; 
	(*elem) = (*elem)->next;
	while (*elem && (*elem)->token != '\'')
	{
		str = ft_strjoin(str, (*elem)->content);
		(*elem) = (*elem)->next;
	}
	(*command)->args[*i] = str;
	*i += 1;
	(*elem) = (*elem)->next;
}

void with_d_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	char *str = malloc(sizeof(char) * 100);
	str = ""; 
	(*elem) = (*elem)->next;
	while (*elem && (*elem)->token != '\"')
	{
		if ((*elem)->token == ENV)
		{
			char *dst = get_env(elem, env);
			if (str)
				str = ft_strjoin(str, dst);
		}
		else
			str = ft_strjoin(str, (*elem)->content);
		(*elem) = (*elem)->next;
	}
	(*command)->args[*i] = str;
	*i += 1;
	(*elem) = (*elem)->next;
}

void without_quote(t_elem **elem, t_command **command, int *i, char **env)
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
		{
			char *str = get_env(elem, env);
			if (str)
			{
				(*command)->args[*i] = str;
				*i += 1;
			}
		}
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
	while ((*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
	if ((*elem)->token == QOUTE || (*elem)->token == DOUBLE_QUOTE)
	{
		(*elem) = (*elem)->next;
		while ((*elem)->token != DOUBLE_QUOTE && (*elem)->token != QOUTE)
		{
			if ((*elem)->token == ENV)
			{
				char *str = get_env(elem, env);
				if (str)
					(*command)->cmd = ft_strjoin((*command)->cmd, str);
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
			char *str = get_env(elem, env);
			if (str)
				(*command)->cmd = str;
			else
				command_comand(elem, command, env);
		}
		else
			(*command)->cmd = (*elem)->content;
		(*elem) = (*elem)->next;
	}
}

void stack_command(t_elem *elem, t_command **command, int *i, char **env)
{
	while (elem)
	{
		while (elem && elem->token == WHITE_SPACE)
			elem = elem->next;
		(*command)->cmd = "";
		while (elem && elem->token != PIPE_LINE)
		{
			if (elem->token == QOUTE)
				with_quote(&elem, command, i);
			else if (elem->token == DOUBLE_QUOTE)
				with_d_quote(&elem, command, i, env);
			else
				without_quote(&elem, command, i, env);
			if ((*command)->args[0] != NULL)
				(*command)->cmd = (*command)->args[0];
		}
	}
	(*command)->args[*i] = NULL;
}
