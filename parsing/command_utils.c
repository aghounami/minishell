/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:19:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/14 11:36:47 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redeirection(t_command **command, t_elem **elem, t_cmd_utils **utils)
{
	(*command)->redirection[(*utils)->index] = ft_strdup((*elem)->content);
	(*utils)->index += 1;
	(*elem) = (*elem)->next;
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
	if ((*elem) && (*elem)->token != PIPE_LINE)
	{
		(1) && ((*command)->redirection[(*utils)->index] = ft_strdup((*elem)->content), \
			(*command)->check_expand = (*elem)->expand , (*elem) = (*elem)->next, (*utils)->index += 1);
	}
}

void	without_quote(t_elem **elem, t_command **command, char **env, t_cmd_utils **utils)
{
	if (*elem && (*elem)->token == BACK_SLASH)
		(*elem) = (*elem)->next;
	if (*elem && (*elem)->content[0] == '\0')
		(1) && ((*command)->args[(*utils)->i] = ft_strdup((*elem)->content) \
			, (*utils)->i += 1, (*elem) = (*elem)->next);
	(void)env;
	// if ((*elem) && ((*elem)->token == WHITE_SPACE && (*utils)->i > 1 \
	// 	&& strncmp((*command)->cmd, "echo", 4) == 0))
	// {
	// 	while ((*elem) && ((*elem)->token == WHITE_SPACE \
	// 		|| (*elem)->token == BACK_SLASH || (*elem)->token == '\t'))
	// 		(*elem) = (*elem)->next;
	// 	if ((*elem) && (*elem)->token != PIPE_LINE)
	// 		(1) && ((*command)->args[(*utils)->i] = ft_strdup(" "), (*utils)->i += 1);
	// }
	if ((*elem) && ((*elem)->content[0] == '\0' || (*elem)->token == WHITE_SPACE))
		(*elem) = (*elem)->next;
	else if ((*elem) && (*elem)->token == ESCAPE)
		(1) && ((*command)->args[(*utils)->i] = ft_strdup(&(*elem)->content[1]), \
			(*utils)->i += 1, (*elem) = (*elem)->next);
	else
	{
		if((*elem) && ((*elem)->token == REDIR_IN || (*elem)->token == HERE_DOC \
			|| (*elem)->token == REDIR_OUT || (*elem)->token == DREDIR_OUT))
			redeirection(command, elem, utils);
		if ((*elem) && (*elem)->token != WHITE_SPACE && (*elem)->token != BACK_SLASH)
			(1) && ((*command)->args[(*utils)->i] = ft_strdup((*elem)->content), \
				(*utils)->i += 1, (*elem) = (*elem)->next);
	}
}
