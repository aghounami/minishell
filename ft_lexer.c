/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:35:01 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/25 18:40:27 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *lexer(char *line, t_elem **elem)
{
	int i;
	int j;
	t_elem *prev = NULL;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<'
			&& line[i] != '\'' && line[i] != '\"' && line[i] != '\0' && line[i] != '\n'
				&& line[i] != '\t' && line[i] != '\\' && line[i] != '$')
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
			lstadd_back(elem, lstnew(word, WORD, &prev));
		}
		else if (line[i] == '$')
		{
			j = 1;
			char *env = malloc(sizeof(char) * 100);
			env[0] = '$';
			i++;
			while ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9') || line[i] == '_' || line[i] == '?' || line[i] == '$')
			{
				env[j] = line[i];
				j++;
				i++;
				if (j == 2 && (!(env[1] >= 'a' && env[1] <= 'z') && !(env[1] >= 'A' && env[1] <= 'Z')))
					break;
			}
			env[j] = '\0';
			lstadd_back(elem, lstnew(env, ENV, &prev));
		}
		else if (line[i] == ' ' || line[i] == '\t')
		{
			char *space = malloc(sizeof(char) * 2);
			space[0] = ' ';
			space[1] = '\0';
			lstadd_back(elem, lstnew(space, WHITE_SPACE , &prev));
			i++;
		}
		else if (line[i] == '|')
		{
			char *pipe = malloc(sizeof(char) * 2);
			pipe[0] = '|';
			pipe[1] = '\0';
			lstadd_back(elem, lstnew(pipe, PIPE_LINE , &prev));
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
				lstadd_back(elem, lstnew(dredir_out, DREDIR_OUT , &prev));
				i += 2;
			}
			else
			{
				char *redir_out = malloc(sizeof(char) * 2);
				redir_out[0] = '>';
				redir_out[1] = '\0';
				lstadd_back(elem, lstnew(redir_out, REDIR_OUT , &prev));
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
				lstadd_back(elem, lstnew(redir_in, HERE_DOC , &prev));
				i += 2;
			}
			else
			{
				redir_in[0] = '<';
				redir_in[1] = '\0';
				lstadd_back(elem, lstnew(redir_in, REDIR_IN , &prev));
				i++;
			}
		}
		else if (line[i] == '\'')
		{
			char *quote = malloc(sizeof(char) * 2);
			quote[0] = '\'';
			quote[1] = '\0';
			lstadd_back(elem, lstnew(quote, QOUTE , &prev));
			i++;
		}
		else if (line[i] == '\"')
		{
			char *dquote = malloc(sizeof(char) * 2);
			dquote[0] = '\"';
			dquote[1] = '\0';
			lstadd_back(elem, lstnew(dquote, DOUBLE_QUOTE , &prev));
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
			lstadd_back(elem, lstnew(escape, ESCAPE , &prev));
		}
		else
			i++;
	}
	return (elem);
}
