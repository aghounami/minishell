/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:08:23 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/07 20:08:34 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_found(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(" command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

void	search(t_command **command, t_exec *ex)
{
	t_command	*cmd;

	cmd = *command;
	ex->i = 0;
	while (ex->path_split[ex->i])
	{
		if (!ft_isalpha(cmd->args[0][1]))
			break ;
		ex->path = ft_strjoin(ex->path_split[ex->i], "/");
		if (!ex->path)
			ft_exit_fail("path problem");
		ex->exec_path = ft_strjoin(ex->path, cmd->args[0]);
		if (!ex->exec_path)
			ft_exit_fail("exec path problem");
		if (access(ex->exec_path, X_OK) == 0)
		{
			(free(ex->path), ex->flag = 1);
			break ;
		}
		else
			(free(ex->path), free(ex->exec_path), ex->i++, ex->flag = 0);
	}
}

void	search_2(t_command **command, t_exec *ex)
{
	t_command	*cmd;

	cmd = *command;
	ex->current_dir = (char *)malloc(PATH_MAX);
	if (!ex->current_dir)
	{
		perror("search_2");
		exit(1);
	}
	getcwd(ex->current_dir, PATH_MAX);
	ex->path_in = ft_strchr(cmd->args[0], '/');
	ex->exec_path = ft_strjoin(ex->current_dir, ex->path_in);
	if (access(ex->exec_path, X_OK) == 0)
		if (ft_strncmp(ex->current_dir, ex->exec_path, \
			(ft_strlen(ex->exec_path))))
			ex->flag = 1;
	free(ex->current_dir);
}

int	search_3(t_command **command, t_exec *ex)
{
	t_command	*cmd;

	cmd = *command;
	if (ex->flag == 1)
		cmd->exec_path = ex->exec_path;
	else
	{
		if (access(cmd->args[0], X_OK) == 0)
		{
			cmd->exec_path = cmd->args[0];
			ex->flag = 1;
			return (0);
		}
	}
	return (1);
}

void	search_exec_2(t_command **command, t_env **env)
{
	t_command	*exec;
	t_exec		ex;

	ft_memset(&ex, 0, sizeof(t_exec));
	exec = *command;
	ex.flag = 0;
	if (exec->args == NULL || exec->args[0] == NULL || exec->args[0][0] == '\0')
		not_found(exec->args[0]);
	ex.path_split = ft_split(get_envx("PATH", env), ':');
	if (!ex.path_split)
	{
		if (search_3(command, &ex))
			not_found(exec->args[0]);
		return ;
	}
	search(command, &ex);
	if (ex.flag == 0)
		search_2(command, &ex);
	search_3(command, &ex);
	free(ex.path_split);
	if (ex.flag == 0)
		not_found(exec->args[0]);
}
