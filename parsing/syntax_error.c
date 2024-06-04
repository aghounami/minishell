/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:39:14 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/02 16:49:46 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quote_dquote(t_elem **tmp, int token, int *error)
{
	*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->token != token)
		*tmp = (*tmp)->next;
	if (!*tmp)
		*error = 1;
}

void	check_redirection(t_elem **tmp, int *error)
{
	*error = ((*tmp)->token == REDIR_IN && (*tmp)->next->token == REDIR_OUT);
	*error = ((*tmp)->token == REDIR_OUT && (*tmp)->next->token == REDIR_IN);
	*error = ((*tmp)->token == HERE_DOC && (*tmp)->next->token == DREDIR_OUT);
	*error = ((*tmp)->token == DREDIR_OUT && (*tmp)->next->token == HERE_DOC);
	*error = ((*tmp)->token == REDIR_IN && (*tmp)->next->token == DREDIR_OUT);
	*error = ((*tmp)->token == REDIR_OUT && (*tmp)->next->token == REDIR_IN);
}

int	utils_syntax(t_elem **tmp2)
{
	while ((*tmp2) && (*tmp2)->token == WHITE_SPACE)
		(*tmp2) = (*tmp2)->next;
	if (!(*tmp2) || (*tmp2)->token == PIPE_LINE || (*tmp2)->token == REDIR_IN \
		|| (*tmp2)->token == REDIR_OUT || (*tmp2)->token == HERE_DOC \
			|| (*tmp2)->token == DREDIR_OUT)
		return (1);
	return (0);
}

int	next_syntax(t_elem **tmp, int *error, t_elem **tmp2)
{
	if ((*tmp)->token == REDIR_IN || (*tmp)->token == REDIR_OUT \
		|| (*tmp)->token == HERE_DOC || (*tmp)->token == DREDIR_OUT)
	{
		(*tmp2) = (*tmp)->next;
		if (utils_syntax(tmp2))
			return (1);
	}
	check_redirection(tmp, error);
	if (*error)
		return (1);
	else if ((*tmp)->token == ESCAPE && (*tmp)->content[1] == '\0')
	{
		(*tmp) = (*tmp)->next;
		while ((*tmp) && (*tmp)->token == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		if (!(*tmp))
			return (1);
	}
	if ((*tmp)->token == DOUBLE_QUOTE || (*tmp)->token == QOUTE)
	{
		check_quote_dquote(tmp, (*tmp)->token, error);
		if (*error)
			return (1);
	}
	return (0);
}

int	syntax_error(t_elem **elem, int *nbr_hdoc)
{
	t_elem	*tmp;
	t_elem	*tmp2;
	int		error;

	(1) && (error = 0, tmp = *elem);
	if (check_if_pipe_line_first(elem))
		return (1);
	while (tmp)
	{
		if (tmp->token == PIPE_LINE)
		{
			tmp2 = tmp->next;
			while (tmp2 && tmp2->token == WHITE_SPACE)
				tmp2 = tmp2->next;
			if (!tmp2 || tmp2->token == PIPE_LINE)
				return (1);
		}
		if (next_syntax(&tmp, &error, &tmp2))
			return (1);
		if (tmp->token == HERE_DOC)
			(*nbr_hdoc)++;
		tmp = tmp->next;
	}
	return (0);
}
