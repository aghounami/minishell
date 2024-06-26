/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:35:01 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/05 22:05:14 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_redirect(char *line, t_elem **elem, t_lexer *lexer)
{
	if (line[lexer->i + 1] == '>')
	{
		lexer->str[0] = '>';
		lexer->str[1] = '>';
		lexer->str[2] = '\0';
		lexer->i += 2;
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), DREDIR_OUT));
	}
	else
		case_one_char(lexer, elem, line, REDIR_OUT);
}

void	case_herdoc_or_redir(char *line, t_elem **elem, t_lexer *lexer)
{
	if (line[lexer->i + 1] == '<')
	{
		lexer->str[0] = '<';
		lexer->str[1] = '<';
		lexer->str[2] = '\0';
		lexer->i += 2;
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), HERE_DOC));
		if (lexer->in_hrdc == 0)
			lexer->here_doc = 1;
	}
	else
		case_one_char(lexer, elem, line, REDIR_IN);
}

void	case_one_char(t_lexer *lexer, t_elem **elem, char *line, int type)
{
	if (line[lexer->i] == '\'' && lexer->d_quote % 2 == 0)
		lexer->quote += 1;
	if (line[lexer->i] == '\"' && lexer->quote % 2 == 0)
		lexer->d_quote += 1;
	if (line[lexer->i] == '\'' && lexer->quote % 2 == 0 && line[lexer->i + 1] \
		&& (line[lexer->i + 1] == ' ' || line[lexer->i + 1] == '\t' \
			|| line[lexer->i + 1] == '|' || line[lexer->i + 1] == '>' \
				|| line[lexer->i + 1] == '<'))
		lexer->here_doc = 0;
	if (line[lexer->i] == '\"' && lexer->d_quote % 2 == 0 && line[lexer->i + 1] \
		&& (line[lexer->i + 1] == ' ' || line[lexer->i + 1] == '\t' \
			|| line[lexer->i + 1] == '|' || line[lexer->i + 1] == '>' \
				|| line[lexer->i + 1] == '<'))
		lexer->here_doc = 0;
	lexer->str[0] = line[lexer->i];
	lexer->str[1] = '\0';
	lexer->i += 1;
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), type));
}

void	init(t_lexer **lexer, int flag)
{
	(*lexer) = malloc(sizeof(t_lexer));
	if (!*lexer)
		malloc_fail();
	(1) && ((*lexer)->i = 0, (*lexer)->j = 0, \
		(*lexer)->prev = NULL, (*lexer)->quote = 0, \
			(*lexer)->here_doc = 0, (*lexer)->d_quote = 0, \
				(*lexer)->export = 0, (*lexer)->in_hrdc = flag);
}

void	*lexer(char *line, t_elem **elem, char **env, int flag)
{
	t_lexer	*lexer;

	init(&lexer, flag);
	while (line[lexer->i])
	{
		lexer->str = malloc(sizeof(char) * ft_strlen(line) + 1);
		if (!lexer->str)
			malloc_fail();
		if (line[lexer->i] == '$' && (line[lexer->i + 1] == ' ' \
			|| line[lexer->i + 1] == '\t' || line[lexer->i + 1] == '\0'))
			case_one_char(lexer, elem, line, WORD);
		else if (line[lexer->i] == '$' && ((line[lexer->i + 1] == '\'' \
			&& (lexer->quote % 2 != 0 || (flag == 1 && lexer->quote % 2 == 0))) \
				|| (line[lexer->i + 1] == '\"' && (lexer->d_quote % 2 != 0 \
					|| (flag == 1 && lexer->d_quote % 2 == 0)))))
			case_one_char(lexer, elem, line, WORD);
		else if (line[lexer->i] == '$' && line[lexer->i + 1] != '\0' \
			&& line[lexer->i + 1] != ' ' && line[lexer->i + 1] != '\t' \
				&& line[lexer->i + 1] != '+' && line[lexer->i + 1] != '=')
			case_dollar(lexer, elem, line, env);
		else
			next_case(line, elem, lexer);
		free(lexer->str);
	}
	return (free(lexer), elem);
}
