/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:08:57 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/30 02:47:41 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_lexer(t_elem **pars)
{
    t_elem	*tmp2;

    while (*pars)
    {
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
        (*command)->args = NULL;
        free(*command);
        *command = tmp;
    }
}