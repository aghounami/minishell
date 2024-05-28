/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:07:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/28 16:00:15 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (waitpid(-1, 0, WNOHANG) == 0)
		{
			printf("\n");
			return ;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	exit_status(int status)
{
	static int	e_status = 0;

	if (status != -1)
		e_status = status;
	return (e_status);
}

void	init_shlvl(char **env)
{
	int		i;
	char	*old;
	char	*new;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			(1) && (old = ft_strdup(env[i]), tmp = ft_strchr(old, '='));
			tmp++;
			if (ft_atoi(tmp) >= 999)
				new = ft_strdup("");
			else if (tmp[0] == '\0')
				new = ft_strdup("1");
			else
				new = ft_itoa(ft_atoi(tmp) + 1);
			(1) && (free(env[i]), env[i] = ft_join(ft_strdup("SHLVL="), new));
			free(old);
			free(new);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_varr		*var;
	t_command	*command;
	t_elem		*pars;
	t_elem		*list;
	(void)argv;
	(void)argc;
	if (isatty(0) == 0)
		return (0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	var = malloc(sizeof(t_varr));
	if (env[0] == NULL)
	{
		env = malloc(sizeof(char *) * 5);
		env[0] = ft_strdup("PWD=/Users/aghounam/Desktop/minishell");
		env[1] = ft_strdup("SHLVL=1");
		env[2] = ft_strdup("_=/usr/bin/env");
		env[3] = ft_strdup("PATH=/Users/aghounam/.brew/bin:/usr/local/bin:"
			"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:"
			"/Library/Apple/usr/bin:/Users/aghounam/.brew/bin");
		env[4] = NULL;
	}
	(1) && (exit_status(0), var->envp = ft_strdup_2d(env));
	(1) && (init_shlvl(var->envp), rl_catch_signals = 0);
	while (1)
	{
		(1) && (pars = NULL, command = NULL, list = NULL, var->nbr_hdoc = 0);
		var->line = readline("\033[0;30m➜ minishell : \033[0m");
		if (var->line && var->line[0] != '\0')
		{
			lexer(var->line, &pars, var->envp, 0);
			state(&pars, var->envp, 0);
			var->flag = syntax_error(&pars, &var->nbr_hdoc);
			new_linked_list(&pars, &list);
			stack_command(list, &command, var->envp);
			print_comand(command);
			(1) && (var->a = dup(1), var->b = dup(0));
			open_herdoc(&command, var->envp, &var->nbr_hdoc);
			if (var->flag == 0 && command)
				var->envp = exec_check(&command, var->envp);
			else
			{
				exit_status(258);
				printf("\033[0;31mminishell: syntax error\033[0m\n");
			}
			dup2(var->a, 1);
			dup2(var->b, 0);
			(1) && (close(var->a), close(var->b));
			(1) && (var->flag = 0, var->nbr_hdoc = 0);
		}
		else if (!var->line)
		{
			printf("exit\n");
			free(var->line);
			free(var->envp);
			free(var);
			exit(0);
		}
		add_history(var->line);
		free(var->line);
		ft_free_lexer(&list);
		ft_free_command(&command);
	}
	return (0);
}
