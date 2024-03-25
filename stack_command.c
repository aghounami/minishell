/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/25 18:33:09 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env(t_elem **elem, char **env)
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
			break;
		}
		index++;
	}
	return (env_value);
}

void	stack_env(t_elem **elem, char **env)
{
	t_elem *tmp;
	t_elem *tmp2;

	tmp = *elem;
	while (tmp)
	{
		if ((tmp)->token == ENV)
		{
			char *str = get_env(&tmp, env);
			// printf("content = %s\n", (*elem)->content);
			// printf("str = %s\n", str);
			if (str)
			{
				(tmp)->content = str;
				(tmp)->token = WORD;
				tmp = tmp->next;
			}
			else
			{
				tmp2 = tmp->next;
				if(tmp->next)
					tmp->next->prev = tmp->prev;
				if(tmp->prev)
					tmp->prev->next = tmp->next;
				free(tmp);
				tmp = tmp2;
			}
		}
		else
			tmp = tmp->next;
	}
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
	(void)env;
	char *str = malloc(sizeof(char) * 100);
	str = "";
	(*elem) = (*elem)->next;
	while (*elem && (*elem)->token != '\"')
	{
		str = ft_strjoin(str, (*elem)->content);
		(*elem) = (*elem)->next;
	}
	(*command)->args[*i] = str;
	*i += 1;
	(*elem) = (*elem)->next;
}

void without_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	(void)env;
	char *tmp;

	if ((*elem)->token == WHITE_SPACE && strncmp((*command)->cmd, "echo", 4) == 0 && *i > 1)
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
		if ((*elem)->token != WHITE_SPACE)
		{
			(*command)->args[*i] = (*elem)->content;
			*i += 1;
		}
		(*elem) = (*elem)->next;
	}
}

void stack_command(t_elem *elem, t_command **command, char **env)
{
	int i;
	t_command *new;

	while (elem)
	{
		i = 0;
		new = malloc(sizeof(t_command));
		new->cmd = ft_strdup("");
		new->args = malloc(sizeof(char *) * 100);
		if (elem->token == PIPE_LINE)
		{
			new->pipe = 1;
			elem = elem->next;
		}
		while (elem && elem->token == WHITE_SPACE)
			elem = elem->next;
		while (elem && elem->token != PIPE_LINE)
		{
			if (elem->token == QOUTE)
				with_quote(&elem, &new, &i);
			else if (elem->token == DOUBLE_QUOTE)
				with_d_quote(&elem, &new, &i, env);
			else
				without_quote(&elem, &new, &i, env);
			if (i > 0)
				new->cmd = new->args[0];
			if (!elem || elem->token == PIPE_LINE)
			{
				new->args[i] = NULL;
				lstadd_back_command(command, lstnew_command(new->args, new->cmd));
				new = NULL;
				break;
			}
		}
	}
}
