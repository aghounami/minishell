/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:19:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/03 15:25:24 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	with_quote(t_elem **elem, t_command **command, int *i)
{
	if ((*elem)->next)
	{
		(*elem) = (*elem)->next;
		(*command)->args[*i] = ft_strdup((*elem)->content);
		*i += 1;
		(*elem) = (*elem)->next;
		*elem = (*elem)->next;
	}
}

void	with_d_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	(void)env;
	(*elem) = (*elem)->next;
	(*command)->args[*i] = ft_strdup((*elem)->content);
	*i += 1;
	(*elem) = (*elem)->next;
	(*elem) = (*elem)->next;
}

void	without_quote(t_elem **elem, t_command **command, int *i, char **env)
{
	char	*tmp;

	(void)env;
	if ((*elem) && ((*elem)->token == WHITE_SPACE && *i > 1 \
		&& strncmp((*command)->cmd, "echo", 4) == 0))
	{
		tmp = ft_strdup((*elem)->content);
		while ((*elem) && ((*elem)->token == WHITE_SPACE \
			|| (*elem)->content[0] == '\0'))
			(*elem) = (*elem)->next;
		if ((*elem) && (*elem)->token != PIPE_LINE)
			(1) && ((*command)->args[*i] = tmp, *i += 1);
	}
	else if ((*elem) && (*elem)->token == ESCAPE)
		(1) && ((*command)->args[*i] = ft_strdup(&(*elem)->content[1]), \
			*i += 1, (*elem) = (*elem)->next);
	else
	{
		if ((*elem) && (*elem)->token != WHITE_SPACE \
			&& (*elem)->content[0] != '\0')
			(1) && ((*command)->args[*i] = ft_strdup((*elem)->content), \
				*i += 1);
		(*elem) = (*elem)->next;
		int j = ft_strlen((*command)->args[*i - 1]);
		if ((*elem) && (*elem)->flag_env == 1 && (*command)->args[*i - 1][j - 1] == '=')
		{
			(*command)->args[*i - 1] = ft_strjoin((*command)->args[*i - 1], (*elem)->content);
			(*elem) = (*elem)->next;
		}
	}
}
