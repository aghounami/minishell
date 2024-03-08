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
    // t_elem *head = NULL;
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
            tmp = lstnew(word);
            tmp->token = WORD;
            lstadd_back(elem, tmp);
        }
        else if (line[i] == ' ')
        {
            char *space = malloc(sizeof(char) * 2);
            space[0] = ' ';
            space[1] = '\0';
            tmp = lstnew(space);
            tmp->token = WHITE_SPACE;
            lstadd_back(elem, tmp);
            i++;
        }
        else if (line[i] == '|')
        {
            char *pipe = malloc(sizeof(char) * 2);
            pipe[0] = '|';
            pipe[1] = '\0';
            tmp = lstnew(pipe);
            tmp->token = PIPE_LINE;
            lstadd_back(elem, tmp);
            i++;
        }
        else if (line[i] == '>')
        {
            char *redir_out = malloc(sizeof(char) * 2);
            redir_out[0] = '>';
            redir_out[1] = '\0';
            tmp = lstnew(redir_out);
            tmp->token = REDIR_OUT;
            lstadd_back(elem, tmp);
            i++;
        }
        else if (line[i] == '<')
        {
            char *redir_in = malloc(sizeof(char) * 2);
            redir_in[0] = '<';
            redir_in[1] = '\0';
            tmp = lstnew(redir_in);
            tmp->token = REDIR_IN;
            lstadd_back(elem, tmp);
            i++;
        }
        else if (line[i] == '\'')
        {
            char *quote = malloc(sizeof(char) * 2);
            quote[0] = '\'';
            quote[1] = '\0';
            tmp = lstnew(quote);
            tmp->token = QOUTE;
            lstadd_back(elem, tmp);
            i++;
        }
        else if (line[i] == '\"')
        {
            char *dquote = malloc(sizeof(char) * 2);
            dquote[0] = '\"';
            dquote[1] = '\0';
            tmp = lstnew(dquote);
            tmp->token = DOUBLE_QUOTE;
            lstadd_back(elem, tmp);
            i++;
        }
        else if (line[i] == '\n')
        {
            char *newline = malloc(sizeof(char) * 2);
            newline[0] = '\n';
            newline[1] = '\0';
            tmp = lstnew(newline);
            tmp->token = NEW_LINE;
            lstadd_back(elem, tmp);
            i++;
        }
    }
    return (elem);
}
