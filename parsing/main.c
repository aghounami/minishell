/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:07:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/04 16:53:20 by hel-magh         ###   ########.fr       */
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
			exit_status(128 + signo);
			g_catch = 1;
			return ;
		}
		exit_status(1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		if (waitpid(-1, 0, WNOHANG) == 0)
		{
			printf("Quit: 3\n");
			exit_status(128 + signo);
			g_catch = 1;
			return ;
		}
	}
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

void	pars_exec(t_elem **pars, t_elem **list, t_varr **var, \
	t_command **command)
{
	(1) && (*pars = NULL, *command = NULL, *list = NULL,
			(*var)->nbr_hdoc = 0, g_catch = 0);
	(*var)->line = readline("➜ minishell : ");
	if ((*var)->line && (*var)->line[0] != '\0')
	{
		lexer((*var)->line, pars, (*var)->envp, 0);
		state(pars, (*var)->envp, 0);
		(*var)->flag = syntax_error(pars, &(*var)->nbr_hdoc);
		(1) && (new_linked_list(pars, list), g_catch = (*var)->flag);
		(1) && (stack_command(*list, command, (*var)->envp), g_catch = 0);
		(1) && ((*var)->a = dup(1), (*var)->b = dup(0));
		open_herdoc(command, (*var)->envp, &(*var)->nbr_hdoc);
		if ((*var)->flag == 0 && *command)
			(*var)->envp = exec_check(command, (*var)->envp, (*var)->enp);
		else if ((*var)->flag == 1)
			er_print(":", "syntax error\n", 258);
		(1) && (dup2((*var)->a, 1), dup2((*var)->b, 0), (*var)->flag = 0);
		(1) && (close((*var)->a), close((*var)->b), (*var)->nbr_hdoc = 0);
	}
	else if (!(*var)->line)
		empty_line(var);
	free_all(list, command, var);
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
	if (!var)
		malloc_fail();
	var->enp = 0;
	if (env[0] == NULL)
		empty_env(&var);
	else
		var->envp = ft_strdup_2d(env);
	(1) && (init_shlvl(var->envp), exit_status(0), rl_catch_signals = 0);
	while (1)
		pars_exec(&pars, &list, &var, &command);
	return (0);
}
