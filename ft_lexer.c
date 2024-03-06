/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:35:01 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/05 16:43:00 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *lexer(char *line, t_elem **elem)
{
    int i;
    int j;
    t_elem *head = NULL;
    t_elem *tmp;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '\'' && line[i] != '\"' \
            && line [i] != '\0' && line[i] != '\n' && line[i] != '\t')
        {
            char *word = malloc(sizeof(char) * 100);
            j = 0;
            while (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '\'' && line[i] != '\"' \
                && line[i] != '\0' && line[i] != '\n' && line[i] != '\t')
            {
                word[j] = line[i];
                j++;
                i++;
            }
            word[j] = '\0';
            if (!(head))
            {
                head = lstnew(word);
                head->token = WORD;
            }
            else
            {
                tmp = lstnew(word);
                tmp->token = WORD;
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            // tmp = NULL;
        }
        else if (line[i] == ' ')
        {
            char *word = malloc(sizeof(char) * 100);
            word[0] = ' ';
            word[1] = '\0';
            if (!(head))
                head = lstnew(word);
            else
            {
                tmp = lstnew(word);
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            // tmp->token = WHITE_SPACE;
            while (line[i] == ' ')
                i++;
        }
        else if (line[i] == '|')
        {
            char *word = malloc(sizeof(char) * 100);
            word[0] = '|';
            word[1] = '\0';
            if (!(head))
                head = lstnew(word);
            else
            {
                tmp = lstnew(word);
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            // tmp->token = PIPE_LINE;
            i++;
        }
        else if (line[i] == '>')
        {
            char *word = malloc(sizeof(char) * 100);
            word[0] = '>';
            if (line[i + 1] == '>')
            {
                word[1] = '>';
                word[2] = '\0';
                i++;
            }
            else
                word[1] = '\0';
            if (!(head))
                head = lstnew(word);
            else
            {
                tmp = lstnew(word);
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            // if (line[i + 1] == '>')
            //     tmp->token = DREDIR_OUT;
            // else
            //     tmp->token = REDIR_OUT;
            i++;
        }
        else if (line[i] == '<')
        {
            char *word = malloc(sizeof(char) * 100);
            word[0] = '<';
            if (line[1 + i] == '<')
            {
                word[1] = '<';
                word[2] = '\0';
                i++;
            }
            else
                word[1] = '\0';
            if (!(head))
                head = lstnew(word);
            else
            {
                tmp = lstnew(word);
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            if (line[i + 1] == '<')
                tmp->token = HERE_DOC;
            else
                tmp->token = REDIR_IN;
            i++;
        }
        else if (line [i] == '\'')
        {
            char *quote = malloc(sizeof(char) * 100);
            quote[0] = '\'';
            quote[1] = '\0';
            if (!(head))
                head = lstnew(quote);
            else
            {
                tmp = lstnew(quote);
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            // tmp->token = QOUTE;
            i++;
        }
        else if (line[i] == '\"')
        {
            char *quote = malloc(sizeof(char) * 100);
            quote[0] = '\"';
            quote[1] = '\0';
            if (!(head))
                head = lstnew(quote);
            else
            {
                tmp = lstnew(quote);
                lstadd_back(&head, tmp);
                tmp = NULL;
            }
            // tmp->token = DOUBLE_QUOTE;
            i++;
        }
        else
            i++;
    }
    *elem = head;
    return (NULL);
}
