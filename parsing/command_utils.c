/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:19:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/17 11:43:14 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redeirection(t_command **command, t_elem **elem, t_cmd_utils **utils)
{
	(*command)->rdrect[(*utils)->index] = ft_strdup((*elem)->content);
	(*utils)->index += 1;
	(*elem) = (*elem)->next;
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
	if ((*elem) && (*elem)->token != PIPE_LINE)
	{
		(*command)->rdrect[(*utils)->index] = ft_strdup((*elem)->content);
		(*command)->check_expand = (*elem)->expand;
		(*elem) = (*elem)->next;
		(*utils)->index += 1;
	}
}

void	utils_stack(t_elem **elem, t_command **command, t_cmd_utils **utils)
{
	if ((*elem) && ((*elem)->token == REDIR_IN \
		|| (*elem)->token == HERE_DOC || (*elem)->token == REDIR_OUT \
			|| (*elem)->token == DREDIR_OUT))
		redeirection(command, elem, utils);
	else if ((*elem) && (*elem)->token != WHITE_SPACE \
		&& (*elem)->token != BACK_SLASH)
	{
		(*command)->args[(*utils)->i] = ft_strdup((*elem)->content);
		(1) && ((*utils)->i += 1, (*elem) = (*elem)->next);
	}
}

void	without_quote(t_elem **elem, t_command **command, t_cmd_utils **utils)
{
	if (*elem && (*elem)->token == BACK_SLASH)
		(*elem) = (*elem)->next;
	else if (*elem && (*elem)->content[0] == '\0')
	{
		(*command)->args[(*utils)->i] = ft_strdup((*elem)->content);
		(1) && ((*utils)->i += 1, (*elem) = (*elem)->next);
	}
	else if ((*elem) && ((*elem)->content[0] == '\0' \
		|| (*elem)->token == WHITE_SPACE))
		(*elem) = (*elem)->next;
	else if ((*elem) && (*elem)->token == ESCAPE)
	{
		(*command)->args[(*utils)->i] = ft_strdup(&(*elem)->content[1]);
		(1) && ((*utils)->i += 1, (*elem) = (*elem)->next);
	}
	else
		utils_stack(elem, command, utils);
}

	// if ((*elem) && ((*elem)->token == WHITE_SPACE && (*utils)->i > 1 \
	// 	&& strncmp((*command)->cmd, "echo", 4) == 0))
	// {
	// 	while ((*elem) && ((*elem)->token == WHITE_SPACE \
	// 		|| (*elem)->token == BACK_SLASH || (*elem)->token == '\t'))
	// 		(*elem) = (*elem)->next;
	// 	if ((*elem) && (*elem)->token != PIPE_LINE)
	// 		(1) && ((*command)->args[(*utils)->i] = ft_strdup(" "), (*utils)->i += 1);
	// }