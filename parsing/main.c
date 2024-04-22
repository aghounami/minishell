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
		j = 1;
		if (tmp->cmd)
			printf("cmd     = [%s]\n", tmp->cmd);
		while (tmp->args[i] != NULL)
		{
			printf("arg[%d] = [%s]\n", j, tmp->args[i]);
			i++;
			j++;
		}
		printf("----------\n");
		if (tmp->pipe == 1)
			printf("pipe\n");
		tmp = tmp->next;
	}
}

void printf_pars(t_elem *pars)
{
	t_elem *tmp = pars;
	while (tmp)
	{
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
		printf("|   '%s'     |    %d    |            %s          |           %s            \n", elem->content, elem->len, state, token);
		printf("-------------------------------------------------------------------------------------\n");
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

void	f()
{
	system("lsof -c minishell");
}

int main(int argc, char **argv, char **env)
{
	// atexit(f);

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
	while (1)
	{
		pars = NULL;
		command = NULL;
		list = NULL;
		line = readline("\033[0;30m➜ minishell : \033[0m");
		if (line && line[0] != '\0')
		{
			lexer(line, &pars, env);
			state(&pars, env);
			syntax_error(&pars, &flag);
			if (flag == 0)
			{
				// print_lex(pars);
				new_linked_list(&pars, &list);
				stack_command(list, &command, env);
				// print_comand(command);
				if (command && command->cmd)
					exec_check(&command, env);
			}
			flag = 0;
		}
		else if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		free(line);
		// ft_free_lexer(&pars);
		// ft_free_command(&command);
	}
	return (0);
}
