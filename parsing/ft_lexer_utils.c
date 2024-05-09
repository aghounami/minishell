/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:41 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/09 15:21:50 by aghounam         ###   ########.fr       */
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
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), ESCAPE));
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
		lexer->here_doc = 1;
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
						&& line[lexer->i] != '$' && line[lexer->i] != '>' \
							&& line[lexer->i] != '<')
	{
		lexer->str[lexer->j] = line[lexer->i];
		lexer->j += 1;
		lexer->i += 1;
	}
	lexer->str[lexer->j] = '\0';
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), WORD));
	lexer->here_doc = 0;
}

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

int count_worlds(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
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
		// lexer->var_name = ft_strdup(lexer->str);
		if (lexer->here_doc == 1)
			lstadd_back(elem, lstnew(ft_strdup(lexer->str), WORD));
		else
			lstadd_back(elem, lstnew(ft_strdup(lexer->str), ENV));
		lexer->here_doc = 0;
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
	lexer->str[lexer->j] = '\0';
	value = get_env(lexer->str + 1, env);
	// printf("value: %s\n", value);
	if (value && count_worlds(value) > 1 && lexer->quote % 2 == 0 && lexer->here_doc != 1)
	{
		printf("value: %s\n", value);
		int i = 0;
		while (value[i])
		{
			if (value[i] == ' ')
			{
				lstadd_back(elem, lstnew(ft_strdup(" "), WHITE_SPACE));
				i++;
			}
			else if (value[i] == '\t')
			{
				lstadd_back(elem, lstnew(ft_strdup("\t"), WHITE_SPACE));
				i++;
			}
			else
			{
				int j = 0;
				tmp = malloc(sizeof(char) * 100);
				while (value[i]!= '\0' && value[i] != ' ' && value[i] != '\t')
				{
					tmp[j] = value[i];
					j++;
					i++;
				}
				tmp[j] = '\0';
				lstadd_back(elem, lstnew(ft_strdup(tmp), WORD));
				tmp = NULL;
			}
		}
	}
	else if (lexer->here_doc == 1)
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), WORD));
	else
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), ENV));
	lexer->here_doc = 0;
	free(value);
}
