/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:12:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/30 15:50:21 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pid_env(t_elem *elem)
{
	char	*pid;

	pid = ft_itoa(getpid());
	free((elem)->content);
	elem->content = NULL;
	elem->content = ft_strdup(pid);
	free (pid);
	elem->token = NEW_WORD;
	elem = elem->next;
}

void	find_env(t_elem *elem, char **env)
{
	char	*str;

	str = get_env(elem->content + 1, env);
	free((elem)->content);
	(elem)->content = NULL;
	(elem)->content = ft_strdup(str);
	if (ft_strlen(str) == 0)
		(elem)->token = BACK_SLASH;
	else
		(elem)->token = NEW_WORD;
	elem = elem->next;
	free (str);
}

void	status_value(t_elem *elem)
{
	char	*dst;

	(1) && (free((elem)->content), dst = ft_itoa(exit_status(-1)));
	(1) && (exit_status(0), elem->content = ft_strdup(dst));
	if (ft_strlen(dst) == 0)
		(elem)->token = BACK_SLASH;
	else
		(elem)->token = NEW_WORD;
	(1) && (free (dst), elem = elem->next);
}

void	process_name(t_elem *elem)
{
	char	*dst;

	(1) && (free((elem)->content), dst = ft_strdup("minishell"));
	elem->content = ft_strdup(dst);
	if (ft_strlen(dst) == 0)
		(elem)->token = BACK_SLASH;
	else
		(elem)->token = NEW_WORD;
	(1) && (free (dst), elem = elem->next);
}

void	stack_env(t_elem *elem, char **env, int flag)
{
	while (elem)
	{
		if ((elem)->token == ENV && (elem->state == GENERAL \
			|| elem->state == IN_DQUOTE || (elem->state == IN_QUOTE \
				&& flag == 1)))
		{
			if (elem->content[1] && elem->content[1] == '0')
				process_name(elem);
			else if (elem->content[1] && elem->content[1] == '$')
				pid_env(elem);
			else if (elem->content[1] && elem->content[1] == '?')
				status_value(elem);
			else
				find_env(elem, env);
		}
		else
			elem = elem->next;
	}
}
