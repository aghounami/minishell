/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:01:47 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/15 02:28:31 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void stack_command(t_elem *elem, t_command **command)
{
	int i;

	i = 0;
	while (elem->token == WHITE_SPACE)
		elem = elem->next;
	(*command)->cmd = elem->content;
	if (strncmp((*command)->cmd, "echo", 4) == 0)
	{
		elem = elem->next;
		if (!elem)
		{
			(*command)->args[i] = NULL;
			return ;
		}
		while (elem && elem->token == WHITE_SPACE)
			elem = elem->next;
		while (elem && elem->token != PIPE_LINE)
		{
			if (elem->token == '\'' || elem->token == '\"')
			{
				elem = elem->next;
				while (elem->token != '\'' && elem->token != '\"')
				{
					(*command)->args[i] = elem->content;
					i++;
					elem = elem->next;
				}
			}
			else if (elem->token == WORD || elem->token == WHITE_SPACE)
			{
				if (elem->token == WHITE_SPACE)
				{
					while (elem && elem->next && elem->next->token == WHITE_SPACE)
						elem = elem->next;
					if (elem->next)
					{
						(*command)->args[i] = elem->content;
						i++;
					}
				}
				else
				{
					(*command)->args[i] = elem->content;
					i++;
				}
			}
			elem = elem->next;
		}
	}
	else
	{
		(*command)->args[i] = elem->content;
		i++;
		elem = elem->next;
		while (elem && elem->token != PIPE_LINE)
		{
			if (elem->token != WHITE_SPACE)
			{
				(*command)->args[i] = elem->content;
				i++;
			}
			elem = elem->next;
		}
	}
	(*command)->args[i] = NULL;
}
