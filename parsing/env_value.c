/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:12:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/03 15:12:48 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *str, char **env)
{
	int		index;
	int		j;
	char	*env_name;
	char	*env_value;

	(1) && (index = 0, j = 0, env_value = NULL), env_name = ft_strdup(str);
	while (env[index])
	{
		if (ft_strncmp(env[index], env_name, ft_strlen(env_name)) == 0 \
			&& env[index][ft_strlen(env_name)] == '=')
		{
			while (env[index][j] != '=')
				j++;
			env_value = ft_strdup(env[index] + j + 1);
			break ;
		}
		index++;
	}
	free(env_name);
	if (env_value == NULL)
		env_value = ft_strdup("");
	return (env_value);
}

void	pid_env(t_elem *elem)
{
	char	*pid;

	pid = ft_itoa(getpid());
	free((elem)->content);
	elem->content = NULL;
	elem->content = ft_strdup(pid);
	elem->token = WORD;
	elem = elem->next;
}

void	find_env(t_elem *elem, char **env)
{
	char	*str;

	str = get_env(elem->content + 1, env);
	free((elem)->content);
	(elem)->content = NULL;
	(elem)->content = ft_strdup(str);
	(elem)->token = WORD;
	elem = elem->next;
	str = NULL;
}

void	stack_env(t_elem *elem, char **env)
{
	char	*dst;

	while (elem)
	{
		if ((elem)->token == ENV && (elem->state == GENERAL \
			|| elem->state == IN_DQUOTE))
		{
			if (elem->content[1] && elem->content[1] == '0')
			{
				free((elem)->content);
				dst = ft_strdup("minishell");
				elem->content = dst;
				elem->token = WORD;
				elem = elem->next;
				dst = NULL;
			}
			else if (elem->content[1] && elem->content[1] == '$')
				pid_env(elem);
			else
				find_env(elem, env);
		}
		else
			elem = elem->next;
	}
}