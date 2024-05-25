/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:08:57 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/25 21:22:51 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (NULL);
	ft_strlcpy(res, s1, total);
	ft_strlcpy(res + lens1, s2, total);
	if (s1)
		free((char *)s1);
	return (res);
}

void	ft_free_lexer(t_elem **pars)
{
	t_elem	*tmp2;

	while (*pars)
	{
		// printf("freeing");
		tmp2 = (*pars)->next;
		free((*pars)->content);
		free(*pars);
		*pars = tmp2;
	}
}

void	ft_free_command(t_command **command)
{
	t_command	*tmp;
	int			i;

	while (*command)
	{
		tmp = (*command)->next;
		if ((*command)->cmd)
			free((*command)->cmd);
		i = 0;
		while ((*command)->args[i])
		{
			free((*command)->args[i]);
			i++;
		}
		free((*command)->args);
		i = 0;
		while ((*command)->rdrect[i])
		{
			free((*command)->rdrect[i]);
			i++;
		}
		free((*command)->rdrect);
		free(*command);
		*command = tmp;
	}
}
