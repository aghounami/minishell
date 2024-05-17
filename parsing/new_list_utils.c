/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:47:12 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/15 19:05:48 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	special_case(t_elem **tmp, char *str, t_elem **list, int n)
{
	int	i;
	(void)str;
	char *tmp_str;

	tmp_str = ft_strdup("");
	i = 0;
	while (*tmp)
	{
	// printf("here\n");
		if ((*tmp)->token == QOUTE && i == 0)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next, n = 1);
		else if ((*tmp)->token == DOUBLE_QUOTE && i == 0)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next, n = 2);
		else if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			if ((*tmp)->state == GENERAL)
			{
				if (i == 0)
				{
					ft_lstadd_back_new_list(list, lst_new(" ", WHITE_SPACE, \
						GENERAL, NO));
					(*tmp) = (*tmp)->next;
					free(tmp_str);
					return;
				}
				else
					break ;
			}
			else
				(1) && (tmp_str = ft_join(tmp_str, (*tmp)->content), \
					(*tmp) = (*tmp)->next);
		}
		else if ((*tmp)->token == QOUTE && i != 0 && n == 1)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->token == DOUBLE_QUOTE && i != 0 && n == 2)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->content[0] == '\0')
			(*tmp) = (*tmp)->next;
		else if (((*tmp)->token == REDIR_IN || (*tmp)->token == REDIR_OUT \
			|| (*tmp)->token == DREDIR_OUT || (*tmp)->token == HERE_DOC) && i % 2 == 0)
			break ;
		else
			(1) && (tmp_str = ft_join(tmp_str, (*tmp)->content), \
				(*tmp) = (*tmp)->next);
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_QUOTE, NO));
	free(tmp_str);
}

t_elem	*lst_new(char *content, int token, int state, int flag_env)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->token = token;
	new->flag_env = flag_env;
	new->state = state;
	new->expand = 1;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_new_list(t_elem **lst, t_elem *new)
{
	t_elem	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	case_single_quote(t_elem **tmp, char *str, t_elem **list, int n)
{
	int	i;
	(void)str;
	(void)n;
	char *tmp_str;

	(1) && (tmp_str = ft_strdup(""), i = 0);
	while (*tmp)
	{
		if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			if ((*tmp)->state == GENERAL)
			{
				if (i == 0)
				{
					ft_lstadd_back_new_list(list, lst_new(" ", WHITE_SPACE, \
						GENERAL, NO));
					(*tmp) = (*tmp)->next;
					free(tmp_str);
					return;
				}
				else
					break ;
			}
			else
				(1) && (tmp_str = ft_join(tmp_str, (*tmp)->content), \
					(*tmp) = (*tmp)->next);
		}
		else if ((*tmp)->token == QOUTE)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next);
		else if ((*tmp)->token == DOUBLE_QUOTE && i % 2 == 0)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->content[0] == '\0')
			(*tmp) = (*tmp)->next;
		else if (((*tmp)->token == REDIR_IN || (*tmp)->token == REDIR_OUT \
			|| (*tmp)->token == DREDIR_OUT || (*tmp)->token == HERE_DOC) && i % 2 == 0)
			break ;
		else
			(1) && (tmp_str = ft_join(tmp_str, (*tmp)->content), \
				(*tmp) = (*tmp)->next);
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_QUOTE, NO));
	free(tmp_str);
}

void	case_double_quote(t_elem **tmp, char *str, t_elem **list, int n)
{
	int	i;
	(void)str;
	(void)n;
	char *tmp_str;

	(1) && (tmp_str = ft_strdup(""), i = 0);
	while (*tmp)
	{
		if ((*tmp)->token == WHITE_SPACE || (*tmp)->token == PIPE_LINE)
		{
			if ((*tmp)->state == GENERAL)
			{
				if (i == 0)
				{
					ft_lstadd_back_new_list(list, lst_new(" ", WHITE_SPACE, \
						GENERAL, NO));
					(*tmp) = (*tmp)->next;
					free(tmp_str);
					return;
				}
				else
					break ;
			}
			else
				(1) && (tmp_str = ft_join(tmp_str, (*tmp)->content), \
					(*tmp) = (*tmp)->next);
		}
		if ((*tmp)->token == DOUBLE_QUOTE)
			(1) && (i = i + 1, (*tmp) = (*tmp)->next);
		else if ((*tmp)->token == QOUTE && i % 2 == 0)
			(*tmp) = (*tmp)->next;
		else if ((*tmp)->content[0] == '\0')
			(*tmp) = (*tmp)->next;
		else if (((*tmp)->token == REDIR_IN || (*tmp)->token == REDIR_OUT \
			|| (*tmp)->token == DREDIR_OUT || (*tmp)->token == HERE_DOC) && (*tmp)->state == GENERAL)
			break ;
		else
			(1) && (tmp_str = ft_join(tmp_str, (*tmp)->content), \
				(*tmp) = (*tmp)->next);
	}
	ft_lstadd_back_new_list(list, lst_new(tmp_str, WORD, IN_DQUOTE, NO));
	free(tmp_str);
}
