/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:07:43 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/25 21:32:14 by aghounam         ###   ########.fr       */
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

int	exit_status(int status)
{
	static int	e_status = 0;

	if (status != -1)
		e_status = status;
	return (e_status);
}

void	over_write(t_elem **elem, char **line)
{
	t_elem	*tmp;

	tmp = *elem;
	while (tmp)
	{
		*line = ft_join(*line, tmp->content);
		tmp = tmp->next;	
	}
	ft_free_lexer(elem);
}

int herdoc(t_command **command, char **envp)
{
    t_command *cmd = *command;
	t_elem *elem;
	
    int i = 0;
    cmd->here_doc = 0;
    char *temp_filename = "/tmp/here_doc.txt";
    char *line;
     
    while(cmd->rdrect[i])
    { 
        if (ft_strncmp(cmd->rdrect[i], "<<", 3) == 0)
        { 
            i++;
			if (cmd->rdrect[i] == NULL)
				break ;
            char *delimiter = cmd->rdrect[i];
            unlink(temp_filename);
            int fd2 = open(temp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
            cmd->fd = open(temp_filename, O_RDONLY);
            unlink(temp_filename);
			int fd = fork();
			if (fd == 0)
			{
            	while (1)
            	{
					elem = NULL;
            	    line = readline("> ");
            	    if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && ft_strlen(line) == ft_strlen(delimiter)))
            	    {
            	       free(line);
            	       break;
            	    }
					if (line && line[0] != '\0' && cmd->check_expand == 0)
					{
						lexer(line, &elem, envp);
						state(&elem, envp, 1);
						line = NULL;
						over_write(&elem, &line);
					}
            	    write(fd2, line, ft_strlen(line));
            	    write(fd2, "\n", 1);
            	    free(line);
            	}
				exit(0);
			}
			waitpid(fd, NULL, 0);
            close(fd2);
            cmd->here_doc = 1;
        }
        i++;
    }
    return(0);
}

void	open_herdoc(t_command **command, char **envp)
{
	t_command	*cmd;

	cmd = *command;
	cmd->fd = 0;
	while (cmd)
	{
		herdoc(&cmd, envp);
		if (cmd->fd == -1)
			break ;
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		**envp;
	char		*line;
	t_command	*command;
	t_elem		*pars;
	t_elem		*list;
	int			flag;
	int			j;
	int			n;

	(void)argv;
	(void)argc;
	if (isatty(0) == 0)
		return (0);
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	exit_status(0);
	envp = ft_strdup_2d(env);
	init_shlvl(envp);
	while (1)
	{
		(1) && (pars = NULL, command = NULL, list = NULL);
		line = readline("\033[0;30m➜ minishell : \033[0m");
		if (line && line[0] != '\0')
		{
			lexer(line, &pars, envp);
			state(&pars, envp, 0);
			flag = syntax_error(&pars);
			new_linked_list(&pars, &list);
			// printf_pars(list);
			stack_command(list, &command, envp);
			// print_comand(command);
			// printf("%d\n", command->fd);
			(1) && (j = dup(1), n = dup(0));
			open_herdoc(&command, envp);
			if (flag == 0 && command)
				flag = 0;
				// envp = exec_check(&command, envp);
			else
			{
				exit_status(258);
				// ft_free_lexer(&pars);
				printf("\033[0;31mminishell: syntax error\033[0m\n");
			}
			dup2(j, 1);
			dup2(n, 0);
			(1) && (close(j), close(n));
			flag = 0;
		}
		else if (!line)
		{
			printf("exit\n");
			free(line);
			free(envp);
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
