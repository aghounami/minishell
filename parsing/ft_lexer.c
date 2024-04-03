/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:35:01 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/02 18:07:01 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_one_char(t_lexer *lexer, t_elem **elem, char *line, int type)
{
	lexer->str[0] = line[lexer->i];
	lexer->str[1] = '\0';
	lexer->i += 1;
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), type, &lexer->prev));
}

void	case_slash(t_lexer *lexer, t_elem **elem, char *line)
{
	int i = 1;
	lexer->str[0] = '\\';
	lexer->i += 1;
	while ((line[lexer->i] >= 'a' && line[lexer->i] <= 'z') \
		|| (line[lexer->i] >= 'A' && line[lexer->i] <= 'Z'))
	{
		lexer->str[i] = line[lexer->i];
		i += 1;
		lexer->i += 1;
	}
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), SLASH, &lexer->prev));
}

void	*lexer(char *line, t_elem **elem, char **env)
{
	t_lexer	*lexer;

	(1) && (lexer = malloc(sizeof(t_lexer)), lexer->i = 0, \
		lexer->j = 0, lexer->prev = NULL);
	while (line[lexer->i])
	{
		lexer->str = ft_calloc(1000, sizeof(char));
		if (line[lexer->i] == '$' && line[lexer->i + 1] != '\0' && line[lexer->i + 1] != ' ' && line[lexer->i + 1] != '\t')
			case_dollar(lexer, elem, line, env);
		else if (line[lexer->i] == '$' && (line[lexer->i + 1] == ' ' || line[lexer->i + 1] == '\t' || line[lexer->i + 1] == '\0'))
			case_one_char(lexer, elem, line, WORD);
		else if (line[lexer->i] == ' ' || line[lexer->i] == '\t')
			case_one_char(lexer, elem, line, WHITE_SPACE);
		else if (line[lexer->i] == '|')
			case_one_char(lexer, elem, line, PIPE_LINE);
		else if (line[lexer->i] == '>')
			case_redirect(line, elem, lexer);
		else if (line[lexer->i] == '<')
			case_herdoc_or_redir(line, elem, lexer);
		else if (line[lexer->i] == '\'')
			case_one_char(lexer, elem, line, QOUTE);
		else if (line[lexer->i] == '\"')
			case_one_char(lexer, elem, line, DOUBLE_QUOTE);
		else if (line[lexer->i] == '\\')
			case_escape(line, elem, lexer);
		// else if (line[lexer->i] == '/')
		// 	case_slash(lexer, elem, line);
		// else if (line[lexer->i] == '=')
		// 	case_one_char(lexer, elem, line, WORD);
		else
			case_word(line, elem, lexer);
		free(lexer->str);
	}
	free(lexer);
	return (elem);
}
