/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:09:08 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/07 20:16:43 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_1(t_elem **tmp)
{
	while (*tmp && (*tmp)->token != DOUBLE_QUOTE)
	{
		(*tmp)->state = IN_DQUOTE;
		*tmp = (*tmp)->next;
	}
}

void	case_2(t_elem **tmp)
{
	while ((*tmp) && (*tmp)->token != QOUTE)
	{
		(*tmp)->state = IN_QUOTE;
		(*tmp) = (*tmp)->next;
	}
}

void	state_2(t_elem **tmp, int *flag_quote, int *flag_d_quote, t_elem **prev)
{
	(1) && ((*tmp)->state = GENERAL, (*prev) = (*tmp));
	if ((*prev)->token == DOUBLE_QUOTE)
		*flag_d_quote = *flag_d_quote + 1;
	if ((*prev)->token == QOUTE)
		flag_quote = flag_quote + 1;
	(*tmp) = (*tmp)->next;
}

void	state(t_elem **elem, char **env, int flag)
{
	t_elem	*tmp;
	int		flag_quote;
	int		flag_d_quote;
	t_elem	*prev;

	(1) && (flag_quote = 1, flag_d_quote = 1, tmp = *elem, prev = NULL);
	while (tmp)
	{
		if (prev && prev->token == DOUBLE_QUOTE \
			&& tmp->token != DOUBLE_QUOTE && flag_d_quote % 2 == 0)
			case_1(&tmp);
		else if (prev && prev->token == QOUTE \
			&& tmp->token != QOUTE && flag_quote % 2 == 0)
			case_2(&tmp);
		else
		{
			(1) && (tmp->state = GENERAL, prev = tmp);
			if (prev->token == DOUBLE_QUOTE)
				flag_d_quote++;
			if (prev->token == QOUTE)
				flag_quote++;
			tmp = tmp->next;
		}
	}
	stack_env(*elem, env, flag);
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	total;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	total = lens1 + lens2 + 1;
	res = (char *)malloc(total);
	if (res == NULL)
		malloc_fail();
	ft_strlcpy(res, s1, total);
	ft_strlcpy(res + lens1, s2, total);
	if (s1)
		free((char *)s1);
	return (res);
}
