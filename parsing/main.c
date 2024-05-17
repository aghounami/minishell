/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:07:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/16 19:57:39 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (ft_atoi(tmp) >= 999)
				new_shlvl = ft_strdup("");
			else if (tmp[0] == '\0')
				new_shlvl = ft_strdup("1");
			else
				new_shlvl = ft_itoa(ft_atoi(tmp) + 1);
			free(env[i]);
			env[i] = ft_join(ft_strdup("SHLVL="), new_shlvl);
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
			if (ft_strncmp(line, command->rdrect[1],\
				ft_strlen(command->rdrect[1])) == 0 \
					&& ft_strlen(command->rdrect[1]) == ft_strlen(line))
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
	if (isatty(0) == 0)
		return (0);
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	char **envp = ft_strdup_2d(env);
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
				// printf_pars(list);
				stack_command(list, &command, envp);
				// print_comand(command);
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
			printf("exits\n");
			exit(0);
		}
		add_history(line);
		free(line);
		ft_free_lexer(&list);
		ft_free_command(&command);
	}
	free (envp);
	return (0);
}
