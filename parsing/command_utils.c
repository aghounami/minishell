/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:19:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/07 10:22:58 by aghounam         ###   ########.fr       */
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

void	without_quote(t_elem **elem, t_command **command, char **env, t_cmd_utils **utils)
{
	char	*tmp;

	(void)env;
	if ((*elem) && ((*elem)->token == WHITE_SPACE && (*utils)->i > 1 \
		&& strncmp((*command)->cmd, "echo", 4) == 0))
	{
		tmp = ft_strdup((*elem)->content);
		while ((*elem) && ((*elem)->token == WHITE_SPACE \
			|| (*elem)->content[0] == '\0'))
			(*elem) = (*elem)->next;
		if ((*elem) && (*elem)->token != PIPE_LINE)
			(1) && ((*command)->args[(*utils)->i] = tmp, (*utils)->i += 1);
	}
	else if ((*elem) && (*elem)->token == ESCAPE)
		(1) && ((*command)->args[(*utils)->i] = ft_strdup(&(*elem)->content[1]), \
			(*utils)->i += 1, (*elem) = (*elem)->next);
	else
	{
		if((*elem) && ((*elem)->token == REDIR_IN || (*elem)->token == HERE_DOC))
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
				(1) && ((*command)->rd_in[(*utils)->in] = ft_strdup((*elem)->content), \
					(*elem) = (*elem)->next, (*utils)->in += 1);
			// printf("rd_in[%d] = [%s]\n", (*utils)->in, (*command)->rd_in[(*utils)->in - 1]);
		}
		if ((*elem) && ((*elem)->token == REDIR_OUT || (*elem)->token == DREDIR_OUT))
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
		if ((*elem) && (*elem)->token != WHITE_SPACE && (*elem)->content[0] != '\0')
			(1) && ((*command)->args[(*utils)->i] = ft_strdup((*elem)->content), \
				(*utils)->i += 1, (*elem) = (*elem)->next);
		if ((*elem) && ((*elem)->token == WHITE_SPACE || (*elem)->content[0] == '\0'))
				(*elem) = (*elem)->next;
	}
}

// int j = ft_strlen((*command)->args[*i - 1]);
// if ((*elem) && (*elem)->flag_env == 1 && ((*command)->args[*i - 1][j - 1] == '=' \
// 	||	(*command)->args[*i - 1][j - 1] == '<' || (*command)->args[*i - 1][j - 1] == '>'))
// {
// 	(*command)->args[*i - 1] = ft_strjoin((*command)->args[*i - 1], (*elem)->content);
// 	(*elem) = (*elem)->next;
// }