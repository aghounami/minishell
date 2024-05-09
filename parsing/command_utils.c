/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:19:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/09 15:23:31 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redeire_out(t_command **command, t_elem **elem, t_cmd_utils **utils)
{
	if ((*elem)->token == REDIR_OUT)
			(*command)->redir_out = 1;
	if ((*elem)->token == DREDIR_OUT)
		(*command)->dredir_out = 1;
	(*command)->rd_out[(*utils)->out] = ft_strdup((*elem)->content);
	(*utils)->out += 1;
	(*elem) = (*elem)->next;
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
	if ((*elem) && (*elem)->token != PIPE_LINE)
		(1) && ((*command)->rd_out[(*utils)->out] = ft_strdup((*elem)->content), \
			(*elem) = (*elem)->next, (*utils)->out += 1);
}

void	redeire_in(t_command **command, t_elem **elem, t_cmd_utils **utils)
{
	if ((*elem)->token == REDIR_IN)
			(*command)->redir_in = 1;
	if ((*elem)->token == HERE_DOC)
			(*command)->here_doc = 1;
	(*command)->rd_in[(*utils)->in] = ft_strdup((*elem)->content);
	(*utils)->in += 1;
	(*elem) = (*elem)->next;
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
	if ((*elem) && (*elem)->token != PIPE_LINE)
	{
		(1) && ((*command)->rd_in[(*utils)->in] = ft_strdup((*elem)->content), \
			(*elem) = (*elem)->next, (*utils)->in += 1);
	}
}

void	without_quote(t_elem **elem, t_command **command, char **env, t_cmd_utils **utils)
{

	(void)env;
	if ((*elem) && ((*elem)->token == WHITE_SPACE && (*utils)->i > 1 \
		&& strncmp((*command)->cmd, "echo", 4) == 0))
	{
		while ((*elem) && ((*elem)->token == WHITE_SPACE \
			|| (*elem)->content[0] == '\0' || (*elem)->token == '\t'))
			(*elem) = (*elem)->next;
		if ((*elem) && (*elem)->token != PIPE_LINE)
			(1) && ((*command)->args[(*utils)->i] = ft_strdup(" "), (*utils)->i += 1);
	}
	if ((*elem) && ((*elem)->content[0] == '\0' || (*elem)->token == WHITE_SPACE))
		(*elem) = (*elem)->next;
	else if ((*elem) && (*elem)->token == ESCAPE)
		(1) && ((*command)->args[(*utils)->i] = ft_strdup(&(*elem)->content[1]), \
			(*utils)->i += 1, (*elem) = (*elem)->next);
	else
	{
		if((*elem) && ((*elem)->token == REDIR_IN || (*elem)->token == HERE_DOC))
			redeire_in(command, elem, utils);
		if ((*elem) && ((*elem)->token == REDIR_OUT || (*elem)->token == DREDIR_OUT))
			redeire_out(command, elem, utils);
		if ((*elem) && (*elem)->token != WHITE_SPACE && (*elem)->content[0] != '\0')
			(1) && ((*command)->args[(*utils)->i] = ft_strdup((*elem)->content), \
				(*utils)->i += 1, (*elem) = (*elem)->next);
	}
}
