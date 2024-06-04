/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:51 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/02 19:25:55 by aghounam         ###   ########.fr       */
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
		malloc_fail();
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*get_env(char *str, char **env)
{
	int		index;
	int		j;
	char	*env_name;
	char	*env_value;

	(1) && (index = 0, j = 0, env_value = NULL), env_name = ft_strdup(str);
	while (env[index])
	{
		if (ft_strncmp(env[index], env_name, ft_strlen(env_name)) == 0 \
			&& env[index][ft_strlen(env_name)] == '=')
		{
			while (env[index][j] != '=')
				j++;
			env_value = ft_strdup(env[index] + j + 1);
			break ;
		}
		index++;
	}
	free(env_name);
	if (env_value == NULL)
		env_value = ft_strdup("");
	return (env_value);
}
