/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:51 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/21 17:59:17 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	next_case(char *line, t_elem **elem, t_lexer *lexer)
{
	if (line[lexer->i] == '>')
		case_redirect(line, elem, lexer);
	else if (line[lexer->i] == '<')
		case_herdoc_or_redir(line, elem, lexer);
	else if (line[lexer->i] == '\'')
		case_one_char(lexer, elem, line, QOUTE);
	else if (line[lexer->i] == '\"')
		case_one_char(lexer, elem, line, DOUBLE_QUOTE);
	else if (line[lexer->i] == '\\')
		case_escape(line, elem, lexer);
	else if (line[lexer->i] == ' ' || line[lexer->i] == '\t')
		case_one_char(lexer, elem, line, WHITE_SPACE);
	else if (line[lexer->i] == '|')
		case_one_char(lexer, elem, line, PIPE_LINE);
	else
		case_word(line, elem, lexer);
}

char	**ft_strdup_2d(char **str)
{
	int		i;
	char	**new;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
