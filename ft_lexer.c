/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:35:01 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/26 17:34:12 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void case_dollar(char *line, int *i, char *str, int *j, t_elem **elem, t_elem *prev)
{
	*j = 1;
	str[0] = '$';
	*i += 1;
	while ((line[*i] >= 'a' && line[*i] <= 'z') || (line[*i] >= 'A' \
		&& line[*i] <= 'Z') || (line[*i] >= '0' && line[*i] <= '9') \
			|| line[*i] == '_' || line[*i] == '?' || line[*i] == '$')
	{
		str[*j] = line[*i];
		*j += 1;
		*i += 1;
		if (*j == 2 && (!(str[1] >= 'a' && str[1] <= 'z') \
			&& !(str[1] >= 'A' && str[1] <= 'Z')))
			break;
	}
	str[*j] = '\0';
	lstadd_back(elem, lstnew(ft_strdup(str), ENV, &prev));
}

void case_one_char(int *i, char *str, char c, int type, t_elem **elem, t_elem *prev)
{
	str[0] = c;
	str[1] = '\0';
	*i += 1;
	lstadd_back(elem, lstnew(ft_strdup(str), type, &prev));
}

void case_word(char *line, int *i, char *str, t_elem **elem, t_elem *prev)
{
	int j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '|' && line[*i] != '>'  && line[*i] != '<' \
		&& line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0' \
			&& line[*i] != '\n' && line[*i] != '\t' && line[*i] != '\\')
	{
		str[j] = line[*i];
		j += 1;
		*i += 1;
	}
	str[j] = '\0';
	lstadd_back(elem, lstnew(ft_strdup(str), WORD, &prev));
}

void *lexer(char *line, t_elem **elem)
{
	char *str;
	int i;
	int j;
	t_elem *prev = NULL;

	i = 0;
	while (line[i])
	{
		str = malloc(sizeof(char) * 100);
		if (line[i] == '$')
			case_dollar(line, &i, str, &j, elem, prev);
		else if (line[i] == ' ' || line[i] == '\t')
			case_one_char(&i, str, ' ', WHITE_SPACE, elem, prev);
		else if (line[i] == '|')
			case_one_char(&i, str, '|', PIPE_LINE, elem, prev);

		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				str[0] = '>';
				str[1] = '>';
				str[2] = '\0';
				i += 2;
				lstadd_back(elem, lstnew(ft_strdup(str), DREDIR_OUT, &prev));
			}
			else
				case_one_char(&i, str, '>', REDIR_OUT, elem, prev);
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				str[0] = '<';
				str[1] = '<';
				str[2] = '\0';
				i += 2;
				lstadd_back(elem, lstnew(ft_strdup(str), HERE_DOC, &prev));
			}
			else
				case_one_char(&i, str, '<', REDIR_IN, elem, prev);
		}
		else if (line[i] == '\'')
			case_one_char(&i, str, '\'', QOUTE, elem, prev);
		else if (line[i] == '\"')
			case_one_char(&i, str, '\"', DOUBLE_QUOTE, elem, prev);
		else if (line[i] == '\\')
		{
			str[0] = '\\';
			if (line[i + 1] != '\0')
			{
				str[1] = line[i + 1];
				str[2] = '\0';
				i += 2;
			}
			else
			{
				str[1] = '\0';
				i++;
			}
			lstadd_back(elem, lstnew(ft_strdup(str), ESCAPE, &prev));
		}
		else
			case_word(line, &i, str, elem, prev);
		free(str);
	}
	return (elem);
}
