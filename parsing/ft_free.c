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

t_elem    *lst_new(char *content, int token, int state)
{
    t_elem	*new;

    new = (t_elem *)malloc(sizeof(t_elem));
    if (!new)
        return (NULL);
    new->content = ft_strdup(content);
    new->token = token;
    new->state = state;
    new->next = NULL;
    return (new);
}

void   ft_lstadd_back_new_list(t_elem **alst, t_elem *new)
{
    t_elem *tmp;

    if (!*alst)
    {
        *alst = new;
        return ;
    }
    tmp = *alst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    new_linked_list(t_elem **pars, t_elem **list)
{
    t_elem *tmp;
    char *str = NULL;
    tmp = *pars;
    while (tmp && tmp->token == WHITE_SPACE)
       tmp = tmp->next;
    while(tmp)
    {
        if ((tmp->token != QOUTE && tmp->token != DOUBLE_QUOTE) \
            && ((tmp->next && (tmp->next->token != QOUTE \
                && tmp->next->token != DOUBLE_QUOTE)) || !tmp->next))
        {
            printf ("im here1\n");
            str = ft_strdup(tmp->content);
            ft_lstadd_back_new_list(list, lst_new(str, tmp->token, tmp->state));
            // printf("content = [%s]\n", str);
            // free(str);
            str = NULL;
            tmp = tmp->next;
        }
        else
        {
            if (tmp->token == WHITE_SPACE)
            {
                printf("%s\n", tmp->content);
                str = ft_strjoin(str, tmp->content);
                tmp = tmp->next;
            }
            while (tmp)
            {
                // printf ("im here2\n");
                if (tmp->token == WHITE_SPACE || tmp->token == PIPE_LINE)
                {
                    if (tmp->state == GENERAL)
                    {
                        ft_lstadd_back_new_list(list, lst_new(str, WORD, GENERAL));
                        break ;
                    }
                }
                else if (tmp->token == QOUTE  || tmp->token == DOUBLE_QUOTE)
                    tmp = tmp->next;
                else if (tmp->content[0] == '\0')
                    tmp = tmp->next;
                else
                {
                    str = ft_strjoin(str, tmp->content);
                    tmp = tmp->next;
                }
            }
            ft_lstadd_back_new_list(list, lst_new(str, WORD, GENERAL));
            // free(str);
            str = NULL;
        }
    }
}

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
