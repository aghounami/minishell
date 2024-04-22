/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/04/19 10:26:16 by aghounam         ###   ########.fr       */
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

void	exec_check(t_command **command, char **env)
{
	(*command)->evr = env;
	if ((*command)->next == NULL)
	{
		one_cmd(command, env, 0, 0);
		return;
	}
	execution_cmd(command, env);
}
