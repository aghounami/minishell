/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:52:21 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/16 00:00:40 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *check_state(t_elem *elem)
{
	char *state = NULL;
	if (elem->state == IN_DQUOTE)
		state = "IN_DOUBLE_QUOTE";
	else if (elem->state == IN_QUOTE)
		state = "IN_QUOTE";
	else if (elem->state == GENERAL)
		state = "GENERAL";
	return (state);
}

char *find_token(t_elem *elem)
{
	char *str = NULL;
	if (elem->token == WORD)
		str = "WORD";
	else if (elem->token == WHITE_SPACE)
		str = "WHITE_SPACE";
	else if (elem->token == QOUTE)
		str = "QOUTE";
	else if (elem->token == DOUBLE_QUOTE)
		str = "DOUBLE_QUOTE";
	else if (elem->token == ESCAPE)
		str = "ESCAPE";
	else if (elem->token == ENV)
		str = "ENV";
	else if (elem->token == PIPE_LINE)
		str = "PIPE_LINE";
	else if (elem->token == REDIR_IN)
		str = "REDIR_IN";
	else if (elem->token == REDIR_OUT)
		str = "REDIR_OUT";
	else if (elem->token == HERE_DOC)
		str = "HERE_DOC";
	else if (elem->token == DREDIR_OUT)
		str = "DREDIR_OUT";
	else if (elem->token == BACK_SLASH)
		str = "BACK_SLASH";
	else if (elem->token == NEW_WORD)
		str = "NEW_WORD";
	return (str);
}

void print_comand(t_command *command)
{
	t_command *tmp = command;
	int i;
	int j;
	while (tmp)
	{
		i = 0;
		j = 0;
		if (tmp->cmd)
			printf("cmd     = [%s]\n", tmp->cmd);
		while (tmp->args && tmp->args[i] != NULL)
		{
			printf("arg[%d] = [%s]\n", j, tmp->args[i]);
			i++;
			j++;
		}
		int k = 0;
		if (tmp->rdrect && tmp->rdrect[k] != NULL)
			printf("\033[0;32m----redirection----\033[0m\n");
		while (tmp->rdrect && tmp->rdrect[k] != NULL)
		{
			if (k % 2 == 0)
				printf("redirection ➜ [%s]\n", tmp->rdrect[k]);
			else if (k % 2 != 0)
				printf("file ➜ [%s]\n", tmp->rdrect[k]);
			k++;
		}
		if (tmp->pipe == 1)
			printf("\033[0;36m------pipe-------\033[0m \n");
		tmp = tmp->next;
	}
}

void printf_pars(t_elem *pars)
{
	t_elem *tmp = pars;
	while (tmp)
	{
		// if (tmp->env_var != NULL)
		// 	printf("env_var = [%s]\n", tmp->env_var);
		// else
		printf("content = [%s]\n", tmp->content);
		tmp = tmp->next;
	}
}

int print_lex(t_elem *elem)
{
	printf("|                                         LEXER                                     |\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("|   Content          |   Length   |        state          |          token          |\n");
	printf("-------------------------------------------------------------------------------------\n");
	while (elem)
	{
		char *token = find_token(elem);
		char *state = check_state(elem);
		elem->len = strlen(elem->content);
		printf("|   '%s'     |    %d    |            %s          |           %s            \n", \
			elem->content, elem->len, state, token);
		printf("-------------------------------------------------------------------------------------\n");
		// printf("%d\n", elem->expand);
		elem = elem->next;
	}
	return (0);
}