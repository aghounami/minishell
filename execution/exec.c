/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/06 10:20:44 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_extention(const char *p, char *const *ag, t_command **s)
{
	t_command	*exec;

	exec = *s;
	if (execve(p, ag, exec->evr) == -1)
	{
		printf("Error: %s: command not found\n", exec->args[0]);
		exit(EXIT_FAILURE);
	}
}

void	search_exec(t_command **command, t_exec *execution)
{
	t_command	*exec;
	t_exec		*p_exec;

	exec = *command;
	p_exec = execution;
	while (p_exec->path_split[p_exec->i])
	{
		p_exec->path = ft_strjoin(p_exec->path_split[p_exec->i], "/");
		if (!p_exec->path)
			ft_exit_fail("path problem");
		p_exec->exec_path = ft_strjoin(p_exec->path, exec->args[0]);
		if (!p_exec->exec_path)
			ft_exit_fail("exec path problem");
		if (access(p_exec->exec_path, X_OK) == 0)
		{
			free(p_exec->path);
			break ;
		}
		else
		{
			free(p_exec->path);
			free(p_exec->exec_path);
			p_exec->i++;
		}
	}
}

void	exec_path_extention(t_command **command, t_exec *execution)
{
	t_command	*exec;
	t_exec		*p_exec;

	exec = *command;
	p_exec = execution;
	search_exec(command, execution);
	free(p_exec->current_dir);
	ft_free_double(p_exec->path_split);
	exec_extention(p_exec->exec_path, exec->args, command);
}

void	exec_path(t_command **command)
{
	t_command	*exec;
	t_exec		p_exec;

	ft_memset(&p_exec, 0, sizeof(p_exec));
	exec = *command;
	(*command)->content = "PATH";
	p_exec.path_in = get_env_exec(command);
	p_exec.current_dir = (char *)malloc(PATH_MAX);
	if (!p_exec.current_dir || getcwd(p_exec.current_dir, PATH_MAX) == NULL)
		ft_exit_fail("current dir problem_exec");
	p_exec.path = ft_strjoin(p_exec.path_in, ":");
	if (!p_exec.path)
		ft_exit_fail("Path problem");
	p_exec.path = ft_strjoin(p_exec.path, p_exec.current_dir);
	if (!p_exec.path)
		ft_exit_fail("Path problem");
	p_exec.path_split = ft_split(p_exec.path, ':');
	if (!p_exec.path_split)
		ft_exit_fail("p_exec.Path_split problem");
	exec_path_extention(command, &p_exec);
}
void search_exec_2(t_command **command, char **env)
{
	t_command *exec;
	t_exec *p_exec;
	int flag_access;
	
	(1) && (flag_access = 0, exec = *command, p_exec = malloc(sizeof(t_exec)));
	if (!p_exec)
		ft_exit_fail("malloc failed");
	p_exec->path_split = ft_split(get_env("PATH", env), ':');
	if (!p_exec->path_split)
		ft_exit_fail("split failed");
	p_exec->i = 0;
	while (p_exec->path_split[p_exec->i])
	{
		p_exec->path = ft_strjoin(p_exec->path_split[p_exec->i], "/");
		if (!p_exec->path)
			ft_exit_fail("path problem");
		p_exec->exec_path = ft_strjoin(p_exec->path, exec->args[0]);
		if (!p_exec->exec_path)
			ft_exit_fail("exec path problem");
		if (access(p_exec->exec_path, X_OK) == 0)
		{
			(1) && (free(p_exec->path), flag_access = 1);
			break;
		}
		else
		{
			free(p_exec->path);
			free(p_exec->exec_path);
			(1) && (p_exec->i++, flag_access = 0);
		}
	}
	if (flag_access == 0)
	{
		p_exec->path = getcwd(p_exec->current_dir, PATH_MAX);
		p_exec->path_in = ft_strchr(exec->args[0], '/');
		p_exec->exec_path = ft_strjoin(p_exec->path, p_exec->path_in);
		if (access(p_exec->exec_path, X_OK) == 0)
			flag_access = 1;
	}
	if(flag_access == 0)
		if (access(exec->args[0], X_OK) == 0)
			flag_access = 1;
	exec->exec_path = p_exec->exec_path;
	free(p_exec->path_split);
	free(p_exec);
	if (flag_access == 0)
	{
		ft_putstr_fd("\033[0;31mminishell: \033[0m", 2);
		ft_putstr_fd("\033[0;31m command not found\033[0m: ", 2);
		ft_putstr_fd(exec->args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}


void one_cmd(t_command **commands, int pid, int status, t_env **envex)
{
	if (command_check(commands, envex) == 0)
		return;
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			search_exec_2(commands,(*commands)->evr);
			if (execve((*commands)->exec_path, (*commands)->args, (*commands)->evr) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	return;
}
void execution_cmd(t_command **commands, char **env, t_env **envex)
{
    int prev_pipe[2], next_pipe[2], status, pid;

    prev_pipe[0] = -1;
    prev_pipe[1] = -1;

    while (*commands != NULL)
	{
        if (pipe(next_pipe) == -1)
		{
            perror("pipe");
            return;
        }
		
        pid = fork();
        if (pid == -1)
		{
            perror("fork");
            return;
        }
        if (pid == 0)
		{
            if ((*commands)->next != NULL)
                (1) && (dup2(next_pipe[1], STDOUT_FILENO), close(next_pipe[0]));
            if (prev_pipe[0] != -1)
				(1) && (dup2(prev_pipe[0], STDIN_FILENO), close(prev_pipe[1]));
			(1) && (close(prev_pipe[0]), close(prev_pipe[1]));
            if (strncmp("exit", (*commands)->args[0], 4) != 0 && command_check(commands, envex) == 1)
			{
                search_exec_2(commands, env);
                if (execve((*commands)->exec_path, (*commands)->args, (*commands)->evr) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
            }
            else
                exit(0);
        }
        else
		{
            if (prev_pipe[0] != -1)
				(1) && (close(prev_pipe[0]), close(prev_pipe[1]));
			(1) && (prev_pipe[0] = next_pipe[0], prev_pipe[1] = next_pipe[1]);
            *commands = (*commands)->next;
        }
    }
    while (wait(&status) > 0);
}
void refiller(char **env, t_env **envex)
{
	t_env *enve;
	char *tmp;
	char *tmp2;
	enve = *envex;
	int i =0;
	while(enve)
	{
		tmp2 = ft_strjoin(enve->vari, "=");
		tmp = ft_strjoin(tmp2, enve->value);
		free(tmp2);
		free(env[i]);
		env[i] = ft_strdup(tmp);
		free(tmp);
		i++;
		enve = enve->next;
	}
}

void	exec_check(t_command **command, char **env)
{
	static t_env *envex;
	ft_filler(&envex, env);
	(*command)->evr = env;
	if ((*command)->next ==NULL)
	{
		one_cmd(command, 0, 0, &envex);
		return;
	}
	execution_cmd(command, env, &envex);
	
}
