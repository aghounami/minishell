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

void	execution_cmd(t_command **command, char **env)
{
    int    fd[2];
    

    while (*command)
    {
        if ((*command)->next)
        {
            pipe(fd);
            if (fork() == 0)
            {
                search_exec_2(command, env);
                execve((*command)->exec_path, (*command)->args, env);
            }
                (*command) = (*command)->next;
        }
        else
        {
            search_exec_2(command, env);
            execve((*command)->exec_path, (*command)->args, env);
        }
        *command = (*command)->next;
    }
}