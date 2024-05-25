/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:41 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/25 19:28:04 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (line[lexer->i] == '=')
			lexer->export += 1;
		lexer->str[lexer->j] = line[lexer->i];
		lexer->j += 1;
		lexer->i += 1;
	}
	lexer->str[lexer->j] = '\0';
	if (ft_strlen(lexer->str) == 6 && ft_strncmp(lexer->str, "export", 6) == 0)
		lexer->export = 1;
	lstadd_back(elem, lstnew(ft_strdup(lexer->str), WORD));
	if (line[lexer->i] && (line[lexer->i] == '\0' || line[lexer->i] == ' ' \
		|| line[lexer->i] == '\t' || line[lexer->i] == '|' || line[lexer->i] == '>' \
			|| line[lexer->i] == '<') && lexer->d_quote % 2 == 0 && lexer->quote % 2 == 0)
		lexer->here_doc = 0;
}

int	count_worlds(char *str)
{
	int	i;
	int	count;

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

void	special_dolar_case(char *value, t_elem **elem)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (value[i])
	{
		if (value[i] == ' ')
			(1) && (lstadd_back(elem, lstnew(ft_strdup(" "), WHITE_SPACE)), \
				i++);
		else if (value[i] == '\t')
			(1) && (lstadd_back(elem, lstnew(ft_strdup("\t"), WHITE_SPACE)),
				i++);
		else
		{
			j = 0;
			tmp = malloc(sizeof(char) * 100);
			while (value[i] != '\0' && value[i] != ' ' && value[i] != '\t')
				(1) && (tmp[j] = value[i], j++, i++);
			tmp[j] = '\0';
			lstadd_back(elem, lstnew(ft_strdup(tmp), WORD));
			(1) && (free (tmp), tmp = NULL);
		}
	}
}

void	case_dollar_utils(t_lexer *lexer, t_elem **elem, char **env, char *line)
{
	char	*value;

	(1) && (lexer->str[lexer->j] = '\0', value = get_env(lexer->str + 1, env));
	if (value && count_worlds(value) > 1 && lexer->quote % 2 == 0 \
		&& lexer->here_doc != 1 && lexer->export != 2)
		special_dolar_case(value, elem);
	else if (lexer->here_doc == 1)
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), NEW_WORD));
	else
		lstadd_back(elem, lstnew(ft_strdup(lexer->str), ENV));
	if (lexer->export == 2)
		lexer->export = 0;
	free(value);
	if (line[lexer->i] && (line[lexer->i] == '\0' || line[lexer->i] == ' ' \
		|| line[lexer->i] == '\t' || line[lexer->i] == '|' || line[lexer->i] == '>' \
			|| line[lexer->i] == '<') && lexer->d_quote % 2 == 0 && lexer->quote % 2 == 0)
		lexer->here_doc = 0;
}

void	case_dollar(t_lexer *lexer, t_elem **elem, char *line, char **env)
{
	(1) && (lexer->j = 1, lexer->str[0] = '$', lexer->i += 1);
	if (line[lexer->i] && line[lexer->i] == '$')
	{
		(1) && (lexer->str[1] = '$', lexer->str[2] = '\0', lexer->i += 1);
		if (lexer->here_doc == 1)
			lstadd_back(elem, lstnew(ft_strdup(lexer->str), WORD));
		else
			lstadd_back(elem, lstnew(ft_strdup(lexer->str), ENV));
		if (line[lexer->i] && (line[lexer->i] == '\0' || line[lexer->i] == ' ' \
		|| line[lexer->i] == '\t' || line[lexer->i] == '|' || line[lexer->i] == '>' \
			|| line[lexer->i] == '<') && lexer->d_quote % 2 == 0 && lexer->quote % 2 == 0)
			lexer->here_doc = 0;
		return ;
	}
	while ((line[lexer->i] >= 'a' && line[lexer->i] <= 'z') \
		|| (line[lexer->i] >= 'A' && line[lexer->i] <= 'Z') \
			|| (line[lexer->i] >= '0' && line[lexer->i] <= '9') \
				|| line[lexer->i] == '_' || line[lexer->i] == '?')
	{
		(1) && (lexer->str[lexer->j] = line[lexer->i], lexer->j += 1);
		lexer->i += 1;
		if (lexer->j == 2 && (!(lexer->str[1] >= 'a' && lexer->str[1] <= 'z') \
			&& !(lexer->str[1] >= 'A' && lexer->str[1] <= 'Z') && lexer->str[1] != '_'))
			break ;
	}
	case_dollar_utils(lexer, elem, env, line);
}
