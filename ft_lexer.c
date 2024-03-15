/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:35:01 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/14 17:15:32 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *lexer(char *line, t_elem **elem)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '\'' && line[i] != '\"' && line[i] != '\0' && line[i] != '\n' && line[i] != '\t' && line[i] != '\\')
		{
			char *word = malloc(sizeof(char) * 100);
			j = 0;
			while (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '\'' && line[i] != '\"' && line[i] != '\0' && line[i] != '\n' && line[i] != '\t' && line[i] != '\\')
			{
				word[j] = line[i];
				j++;
				i++;
			}
			word[j] = '\0';
			if (word[0] == '$')
				lstadd_back(elem, lstnew(word, ENV));
			else
				lstadd_back(elem, lstnew(word, WORD));
		}
		else if (line[i] == ' ')
		{
			char *space = malloc(sizeof(char) * 2);
			space[0] = ' ';
			space[1] = '\0';
			lstadd_back(elem, lstnew(space, WHITE_SPACE));
			i++;
		}
		else if (line[i] == '|')
		{
			char *pipe = malloc(sizeof(char) * 2);
			pipe[0] = '|';
			pipe[1] = '\0';
			lstadd_back(elem, lstnew(pipe, PIPE_LINE));
			i++;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				char *dredir_out = malloc(sizeof(char) * 3);
				dredir_out[0] = '>';
				dredir_out[1] = '>';
				dredir_out[2] = '\0';
				lstadd_back(elem, lstnew(dredir_out, DREDIR_OUT));
				i += 2;
			}
			else
			{
				char *redir_out = malloc(sizeof(char) * 2);
				redir_out[0] = '>';
				redir_out[1] = '\0';
				lstadd_back(elem, lstnew(redir_out, REDIR_OUT));
				i++;
			}
		}
		else if (line[i] == '<')
		{
			char *redir_in = malloc(sizeof(char) * 3);
			if (line[i + 1] == '<')
			{
				redir_in[0] = '<';
				redir_in[1] = '<';
				redir_in[2] = '\0';
				lstadd_back(elem, lstnew(redir_in, HERE_DOC));
				i += 2;
			}
			else
			{
				redir_in[0] = '<';
				redir_in[1] = '\0';
				lstadd_back(elem, lstnew(redir_in, REDIR_IN));
				i++;
			}
		}
		else if (line[i] == '\'')
		{
			char *quote = malloc(sizeof(char) * 2);
			quote[0] = '\'';
			quote[1] = '\0';
			lstadd_back(elem, lstnew(quote, QOUTE));
			i++;
		}
		else if (line[i] == '\"')
		{
			char *dquote = malloc(sizeof(char) * 2);
			dquote[0] = '\"';
			dquote[1] = '\0';
			lstadd_back(elem, lstnew(dquote, DOUBLE_QUOTE));
			i++;
		}
		else if (line[i] == '\\')
		{
			char *escape = malloc(sizeof(char) * 3);
			escape[0] = '\\';
			if (line[i + 1] != '\0')
			{
				escape[1] = line[i + 1];
				escape[2] = '\0';
				i += 2;
			}
			else
			{
				escape[1] = '\0';
				i++;
			}
			lstadd_back(elem, lstnew(escape, ESCAPE));
		}
		else
			i++;
	}
	return (elem);
}
