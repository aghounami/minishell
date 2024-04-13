/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:41:56 by aghounam          #+#    #+#             */
/*   Updated: 2024/04/04 00:58:12 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_exec_2(t_command **command, char **env)
{
    t_command	*exec;
    t_exec		*p_exec;

    exec = *command;
    p_exec = malloc(sizeof(t_exec));
    if (!p_exec)
        ft_exit_fail("malloc failed");
    p_exec->path_split = ft_split(get_env("PATH", env) , ':');
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
    exec->exec_path = p_exec->exec_path;
    free(p_exec->path_split);
    free(p_exec);
}

void	execution_cmd(t_command **commands, char **env) {
    int prev_pipe_fd[2], curr_pipe_fd[2], status;
    pid_t pid;

    prev_pipe_fd[0] = -1; // Initialize to invalid file descriptors
    prev_pipe_fd[1] = -1;

    while (*commands != NULL) {
        if (pipe(curr_pipe_fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            // Child process
            if (prev_pipe_fd[0] != -1) {
                // Redirect stdin from the previous pipe
                dup2(prev_pipe_fd[0], 0);
                close(prev_pipe_fd[0]);
                close(prev_pipe_fd[1]);
            }

            if ((*commands)->next != NULL) {
                // Redirect stdout to the current pipe
                dup2(curr_pipe_fd[1], 1);
                close(curr_pipe_fd[1]);
                close(curr_pipe_fd[0]);
            }

            // Execute the command
            search_exec_2(commands, env);
            if (execve((*commands)->exec_path, (*commands)->args, env) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else {
            // Parent process
            if (prev_pipe_fd[0] != -1) {
                close(prev_pipe_fd[0]);
                close(prev_pipe_fd[1]);
            }
            prev_pipe_fd[0] = curr_pipe_fd[0];
            prev_pipe_fd[1] = curr_pipe_fd[1];

            // Move to the next command
            *commands = (*commands)->next;
        }
    }

    // Close the last pipe
    if (prev_pipe_fd[0] != -1) {
        close(prev_pipe_fd[0]);
        close(prev_pipe_fd[1]);
    }

    // Wait for all child processes to finish
    while (wait(&status) > 0);
}
