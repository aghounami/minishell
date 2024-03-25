/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:39:14 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/25 22:16:13 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	check_if_pipe_line_first(t_elem **elem)
{
	t_elem *tmp;

	tmp = *elem;
	while (tmp && tmp->token == WHITE_SPACE)
		tmp = tmp->next;
	if (tmp && tmp->token == PIPE_LINE)
	{
		printf("syntax error\n");
		return 1;
	}
	return 0;
}

void syntax_error(t_elem **elem , int *flag)
{
	t_elem *tmp;
	t_elem *tmp2;

	tmp = *elem;
	int error = 0;
	if (check_if_pipe_line_first(elem))
	{
		*flag = 1;
		return ;
	}
	while (tmp)
	{
		if (tmp->token == PIPE_LINE || tmp->token == REDIR_IN || tmp->token == REDIR_OUT \
			|| tmp->token == HERE_DOC || tmp->token == DREDIR_OUT)
		{
			tmp2 = tmp->next;
			while (tmp2 && tmp2->token == WHITE_SPACE)
				tmp2 = tmp2->next;
			if (!tmp2 || tmp2->token == PIPE_LINE || tmp2->token == REDIR_IN || tmp2->token == REDIR_OUT \
				|| tmp2->token == HERE_DOC || tmp2->token == DREDIR_OUT)
			{
				error = 1;
				break;
			}
		}
		error = (tmp->token == REDIR_IN && tmp->next->token == REDIR_OUT);
		error = (tmp->token == REDIR_OUT && tmp->next->token == REDIR_IN);
		error = (tmp->token == HERE_DOC && tmp->next->token == DREDIR_OUT);
		error = (tmp->token == DREDIR_OUT && tmp->next->token == HERE_DOC);
		error = (tmp->token == REDIR_IN && tmp->next->token == DREDIR_OUT);
		error = (tmp->token == REDIR_OUT && tmp->next->token == REDIR_IN);
		if (error)
			break;
		else if (tmp->token == ESCAPE && tmp->content[1] == '\0')
		{
			tmp = tmp->next;
			while (tmp && tmp->token == WHITE_SPACE)
				tmp = tmp->next;
			if (!tmp)
			{
				error = 1;
				break;
			}
		}
		if (tmp->token == DOUBLE_QUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token != DOUBLE_QUOTE)
				tmp = tmp->next;
			if (!tmp)
			{
				error = 1;
				break;
			}
		}
		else if (tmp->token == QOUTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token != QOUTE)
				tmp = tmp->next;
			if (!tmp)
			{
				error = 1;
				break;
			}
		}
		tmp = tmp->next;
	}
	if (error)
	{
		*flag = 1;
		printf("syntax error\n");
		return;
	}
}
