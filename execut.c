/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:41:56 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/19 22:35:29 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void one_cmd(t_command **commands, char **env, int pid, int status)
{
	if (command_check(commands) == 0)
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
			search_exec_2(commands, env);
			if (execve((*commands)->exec_path, (*commands)->args, env) == -1)
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
void execution_cmd(t_command **commands, char **env)
{
	int prev_pipe[2];
	int next_pipe[2];
	int status;
	int pid;

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
				(1) && (dup2(prev_pipe[0], STDIN_FILENO), close(prev_pipe[0]));
			(1) && (close(prev_pipe[1]), close(next_pipe[1]));
			if (strncmp("exit", (*commands)->args[0], 4) != 0 && command_check(commands) == 1)
			{
				search_exec_2(commands, env);
				if (execve((*commands)->exec_path, (*commands)->args, env) == -1)
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
	while (wait(&status) > 0)
		;
}

/*
			if (pid == 0) { // Child process
				if ((*commands)->next != NULL) {
					dup2(pipe_fd[1], 1);
					close(pipe_fd[0]);
				}
				if (dup2(pipe_fd[0], 0) == -1) { // Redirect stdin if needed
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(pipe_fd[0]); // Close unused pipe ends
				close(pipe_fd[1]);
				search_exec_2(commands, env);
				if (execve((*commands)->exec_path, (*commands)->args, env) == -1) {
					perror("execve");
					exit(EXIT_FAILURE);
				}
			} else { // Parent process
				if ((*commands)->next != NULL) {
					close(pipe_fd[0]); // Close unused pipe ends
					close(pipe_fd[1]);
				}
				*commands = (*commands)->next;
			}
		}
	}
}

*/

/*
void    first_process(char av[], charenvp[], t_pipex pi)
{
	if (pipe(pi->fd) == -1)
		error("pipe");
	pi->pid = fork();
	if (pi->pid == -1)
		error("fork");
	if (pi->pid == 0)
	{
		pi->infile = open(av[1], O_RDONLY);
		if (pi->infile == -1)
		{
			close(pi->fd[0]);
			close(pi->fd[1]);
			error("infile");
		}
		check_files(dup2(pi->infile, 0), dup2(pi->fd[1], 1),
			close(pi->fd[0]), 0);
		execute(av[2], envp);
	}
	else
	{
		if (waitpid(pi->pid, NULL, 0) == -1)
			error("waitpid function");
		check_files(dup2(pi->fd[0], 0), 0, close(pi->fd[1]), close(pi->fd[0]));
	}
}

void    next_process(charcmd, char env[], t_pipexpi)
{
	if (pipe(pi->fd) == -1)
		error("pipe");
	pi->pid = fork();
	if (pi->pid == -1)
		error("fork");
	if (pi->pid == 0)
	{
		check_files(dup2(pi->fd[1], 1), 0, close(pi->fd[0]), 0);
		execute(cmd, env);
	}
	else
	{
		if (waitpid(pi->pid, NULL, 0) == -1)
			error("waitpid function");
		check_files(dup2(pi->fd[0], 0), 0, close(pi->fd[1]), close(pi->fd[0]));
	}
}

void    last_process(int ac, char av[], charenv[], t_pipex *pi)
{
	if (!pi->here_doc)
		pi->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (pi->here_doc)
		pi->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (pi->outfile == -1)
	{
		close(pi->fd[0]);
		close(pi->fd[1]);
		error("outfile");
	}
	pi->pid = fork();
	if (pi->pid == -1)
		error("fork");
	if (pi->pid == 0)
	{
		check_files(dup2(pi->outfile, 1), 0, close(pi->outfile), 0);
		execute(av[ac - 2], env);
	}
	else
	{
		if (waitpid(pi->pid, NULL, 0) == -1)
			error("waitpid function");
		check_files(0, 0, close(pi->outfile), 0);
	}
}
﻿
*/
