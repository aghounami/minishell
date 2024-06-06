/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:19:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/06 18:29:11 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_file(char *file)
{
	if (file)
		unlink(file);
}

void	redirect_fd(t_command **command, t_elem **elem, t_cmd_utils **utils)
{
	if (g_catch == 0)
	{
		if ((*elem) && (*command)->redir_in)
			(*utils)->fd = open((*elem)->content, O_RDONLY, 0644);
		else if ((*elem) && ((*command)->redir_out || (*command)->dredir_out) \
			&& access((*elem)->content, F_OK) == -1)
		{
			(*utils)->fd = open((*elem)->content, O_RDWR | O_CREAT | O_TRUNC, \
				0644);
			if ((*utils)->fd != -1)
				rm_file((*elem)->content);
		}
		if ((*utils)->ambigous && (*elem) && (*elem)->token == BACK_SLASH \
			&& (*utils)->fd == -1 && g_catch == 0)
			er_print((*elem)->content, ": ambiguous redirect\n", 2);
		else if ((*utils)->ambigous && (*utils)->fd == -1 && g_catch == 0)
			er_print((*elem)->content, ": No such file or directory\n", 2);
		if ((*utils)->fd != 0 && (*utils)->fd != -1)
			close((*utils)->fd);
	}
	g_catch = 0;
}

void	redeirection(t_command **command, t_elem **elem, t_cmd_utils **utils)
{
	(*utils)->fd = 0;
	(*utils)->ambigous = 0;
	if ((*elem) && (*elem)->token == REDIR_IN)
		(1) && ((*command)->redir_in = 1, (*utils)->ambigous = 1);
	else if ((*elem) && ((*elem)->token == REDIR_OUT \
		|| (*elem)->token == DREDIR_OUT))
		(1) && ((*command)->redir_out = 1, (*utils)->ambigous = 1);
	(*command)->rdrect[(*utils)->index] = ft_strdup((*elem)->content);
	(1) && ((*elem) = (*elem)->next, (*utils)->index += 1);
	while ((*elem) && (*elem)->token == WHITE_SPACE)
		(*elem) = (*elem)->next;
	if (g_catch == 0)
		redirect_fd(command, elem, utils);
	if ((*elem) && (*elem)->token != PIPE_LINE)
	{
		(*command)->rdrect[(*utils)->index] = ft_strdup((*elem)->content);
		(*command)->check_expand = (*elem)->expand;
		(1) && ((*elem) = (*elem)->next, (*utils)->index += 1);
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
