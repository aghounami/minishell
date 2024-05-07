/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:41 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/02 10:38:04 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_escape(char *line, t_elem **elem, t_lexer *lexer)
{
	lexer->str[0] = '\\';
	if (line[lexer->i + 1] != '\0')
	{
		lexer->str[1] = line[lexer->i + 1];
		lexer->str[2] = '\0';
		lexer->i += 2;
	}
	else
	{
		lexer->str[1] = '\0';
		lexer->i += 1;
	}
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), ESCAPE, &lexer->prev));
}

void	case_herdoc_or_redir(char *line, t_elem **elem, t_lexer *lexer)
{
	if (line[lexer->i + 1] == '<')
	{
		lexer->str[0] = '<';
		lexer->str[1] = '<';
		lexer->str[2] = '\0';
		lexer->i += 2;
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), HERE_DOC, \
			&lexer->prev));
	}
	else
		case_one_char(lexer, elem, line, REDIR_IN);
}

void	case_word(char *line, t_elem **elem, t_lexer *lexer)
{
	lexer->j = 0;
	while (line[lexer->i] != ' ' && line[lexer->i] != '|' \
			&& line[lexer->i] != '\'' && line[lexer->i] != '\"' \
				&& line[lexer->i] != '\0' && line[lexer->i] != '\n' \
					&& line[lexer->i] != '\t' && line[lexer->i] != '\\' \
						&& line[lexer->i] != '$')
	{
		lexer->str[lexer->j] = line[lexer->i];
		lexer->j += 1;
		lexer->i += 1;
		if ((line[lexer->i] == '>' || line[lexer->i] == '<') \
			&& (line[lexer->i - 1] != '='  && line[lexer->i + 1] != '='))
			break ;
	}
	lexer->str[lexer->j] = '\0';
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), WORD, &lexer->prev));
}

void	case_redirect(char *line, t_elem **elem, t_lexer *lexer)
{
	if (line[lexer->i + 1] == '>')
	{
		lexer->str[0] = '>';
		lexer->str[1] = '>';
		lexer->str[2] = '\0';
		lexer->i += 2;
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), DREDIR_OUT, \
			&lexer->prev));
	}
	else
		case_one_char(lexer, elem, line, REDIR_OUT);
}

int count_worlds(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

void	case_dollar(t_lexer *lexer, t_elem **elem, char *line, char **env)
{
	char *value;
	char *tmp;
	(void)env;
	lexer->j = 1;
	lexer->str[0] = '$';
	lexer->i += 1;
	if (line[lexer->i] && line[lexer->i] == '$')
	{
		lexer->str[1] = '$';
		lexer->str[2] = '\0';
		lexer->i += 1;
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), ENV, &lexer->prev));
		return ;
	}
	while ((line[lexer->i] >= 'a' && line[lexer->i] <= 'z') \
		|| (line[lexer->i] >= 'A' && line[lexer->i] <= 'Z') \
			|| (line[lexer->i] >= '0' && line[lexer->i] <= '9') \
				|| line[lexer->i] == '_' || line[lexer->i] == '?')
	{
		lexer->str[lexer->j] = line[lexer->i];
		lexer->j += 1;
		lexer->i += 1;
		if (lexer->j == 2 && (!(lexer->str[1] >= 'a' && lexer->str[1] <= 'z') \
			&& !(lexer->str[1] >= 'A' && lexer->str[1] <= 'Z')))
			break ;
	}
	// if (lexer->str[0] == '$
	lexer->str[lexer->j] = '\0';
	value = get_env(lexer->str + 1, env);
	if (value && count_worlds(value) > 1 && lexer->quote % 2 == 0)
	{
		int i = 0;
		while (value[i])
		{
			if (value[i] == ' ')
			{
				lstadd_back(elem, lstnew(ft_strdup(" "), WHITE_SPACE, &lexer->prev));
				i++;
			}
			else
			{
				int j = 0;
				tmp = malloc(sizeof(char) * ft_strlen(value));
				while (value[i]!= '\0' && value[i] != ' ')
				{
					tmp[j] = value[i];
					j++;
					i++;
				}
				tmp[j] = '\0';
				lstadd_back(elem, lstnew(ft_strdup(tmp), WORD, &lexer->prev));
				tmp = NULL;
			}
		}
	}
	else
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), ENV, &lexer->prev));
}
