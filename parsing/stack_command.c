/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/30 05:14:45 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env(char *str, char **env)
{
	int index = 0;
	int j = 0;
	char *env_name;
	char *env_value;
	env_name = ft_strdup(str);
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
	free(env_name);
	if (env_value == NULL)
		env_value = ft_strdup("");
	return (env_value);
}

void stack_env(t_elem *elem, char **env)
{
	// t_elem *tmp2;

	while (elem)
	{
		if ((elem)->token == ENV && (elem->state == GENERAL || elem->state == IN_DQUOTE))
		{
			char *str = get_env(elem->content + 1, env);
			free((elem)->content);
			(elem)->content = ft_strdup(str);
			(elem)->token = WORD;
			elem = elem->next;
			free(str);
		}
		else
			elem = elem->next;
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
	(*command)->args[*i] = ft_strdup(str);
	*i += 1;
	(*elem) = (*elem)->next;
	free(str);
}

void with_d_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	(void)env;
	char *str = malloc(sizeof(char) * 100);
	str = "";
	(*elem) = (*elem)->next;
	while (*elem != NULL && (*elem)->token != '\"')
	{
		str = ft_strjoin(str, (*elem)->content);
		(*elem) = (*elem)->next;
	}
	(*command)->args[*i] = ft_strdup(str);
	*i += 1;
	(*elem) = (*elem)->next;
	free(str);
}

void without_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	(void)env;
	char *tmp;
	if ((*elem) && ((*elem)->token == WHITE_SPACE && *i > 1 && strncmp((*command)->cmd, "echo", 4) == 0))
	{
		tmp = ft_strdup((*elem)->content);
		while ((*elem) && ((*elem)->token == WHITE_SPACE || (*elem)->content[0] == '\0'))
			(*elem) = (*elem)->next;
		if ((*elem) && (*elem)->token != PIPE_LINE)
		{
			(*command)->args[*i] = tmp;
			*i += 1;
		}
	}
	else if ((*elem) && (*elem)->token == ESCAPE)
	{
		(*command)->args[*i] = ft_strdup(&(*elem)->content[1]);
		*i += 1;
		(*elem) = (*elem)->next;
	}
	else
	{
		if ((*elem) && (*elem)->token != WHITE_SPACE && (*elem)->content[0] != '\0')
		{
			(*command)->args[*i] = ft_strdup((*elem)->content);
			*i += 1;
		}
		(*elem) = (*elem)->next;
	}
}

void	ft_free_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void stack_command(t_elem *elem, t_command **command, char **env)
{
	int i;
	t_command *new;

	while (elem)
	{
		i = 0;
		new = malloc(sizeof(t_command));
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
				new->cmd = ft_strdup(new->args[0]);
			else
				new->cmd = NULL;
			if (!elem || elem->token == PIPE_LINE)
			{
				new->env = env;
				new->args[i] = NULL;
				lstadd_back_command(command, lstnew_command(new->args, new->cmd));
				ft_free_2d(new->args);
				free(new->cmd);
				free(new);
				new = NULL;
				break;
			}
		}
	}
}
