/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:07:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/14 14:32:46 by aghounam         ###   ########.fr       */
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
		if (tmp->redirection && tmp->redirection[k] != NULL)
			printf("\033[0;32m----redirection----\033[0m\n");
		while (tmp->redirection && tmp->redirection[k] != NULL)
		{
			if (k % 2 == 0)
				printf("redirection ➜ [%s]\n", tmp->redirection[k]);
			else if (k % 2 != 0)
				printf("file ➜ [%s]\n", tmp->redirection[k]);
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

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (waitpid(-1, 0, WNOHANG) == 0)
		{
			printf("\n");
			return;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	f()
// {
// 	system("lsof -c minishell");
// }
char **strdup_deuble_araay(char **env)
{
	int i;
	char **new;
	i = 0;
	while (env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new[i] = strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void init_shlvl(char **env)
{
	int i;
	char *shlvl;
	char *new_shlvl;
	char *tmp;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_strdup(env[i]);
			tmp = ft_strchr(shlvl, '=');
			tmp++;
			if (ft_atoi(tmp) == 999)
				new_shlvl = ft_strdup("");
			else if (tmp[0] == '\0')
				new_shlvl = ft_strdup("1");
			else
				new_shlvl = ft_itoa(ft_atoi(tmp) + 1);
			free(env[i]);
			env[i] = ft_strjoin("SHLVL=", new_shlvl);
			free(shlvl);
			free(new_shlvl);
			break;
		}
		i++;
	}
}

void	here_doc(t_command *command)
{
	char *line;
	
	line = NULL;
	while (1)
	{
		if (command->check_expand)
			printf("\033[0;35m expand\n \033[0m");
		line = readline("\033[0;36m> \033[0m");
		if (line && line[0] != '\0')
		{
			if (ft_strncmp(line, command->redirection[1],\
				ft_strlen(command->redirection[1])) == 0 && ft_strlen(command->redirection[1]) == ft_strlen(line))
			{
				free(line);
				break;
			}
			else
				free(line);
		}
		else if (!line)
			return ;
	}
}

int main(int argc, char **argv, char **env)
{
	char *line;
	t_command *command;
	t_elem *pars;
	t_elem *list;
	int flag = 0;
	(void)argv;
	(void)argc;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (isatty(0) == 0)
		return (0);
	char **envp = strdup_deuble_araay(env);
	init_shlvl(envp);
	while (1)
	{
		(1) && (pars = NULL, command = NULL, list = NULL);
		line = readline("\033[0;30m➜ minishell : \033[0m");
		if (line && line[0] != '\0')
		{
			
			lexer(line, &pars, envp);
			state(&pars, envp);
			syntax_error(&pars, &flag);
			if (flag == 0)
			{
				// print_lex(pars);
				new_linked_list(&pars, &list);
				// print_lex(list);
				stack_command(list, &command, envp);
				print_comand(command);
				// if (command && command->redirection \
				// 	&& command->redirection[0] != NULL \
				// 		&& ft_strncmp(command->redirection[0], "<<", 2) == 0)
				// 	here_doc(command);
				int j = dup(1);
				int n = dup(0);
				if (command)
					envp = exec_check(&command, envp);
				dup2(j, 1);
				dup2(n, 0);
			}
			else
				ft_free_lexer(&pars);
			flag = 0;
		}
		else if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		free(line);
	// int i =0;
	// while(envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
		ft_free_lexer(&list);
		ft_free_command(&command);
	}
	free (envp);
	return (0);
}
// 3