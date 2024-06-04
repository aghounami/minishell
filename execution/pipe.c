/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:06 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 17:05:45 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ex_cmd(t_command **command, t_exec *ex, t_env **envex)
{
	t_command	*cmd;
	int			i;

	cmd = *command;
	i = 0;
	fill_ter(cmd->args, envex, 2);
	if (cmd->rdrect[i] != NULL)
	{
		ex->fd = redire(&cmd);
		if (ex->fd < 0)
			(dup2(ex->j, 1), dup2(ex->n, 0), close(ex->j), close(ex->n));
		if (ex->fd != 0)
			close(ex->fd);
	}
	if (cmd->redir_out != 1 && (cmd)->dredir_out != 1)
		dup2(ex->j, 1);
}

void	child_ex(t_command **command, t_exec *ex, t_env **envex, char **env)
{
	t_command	*cmd;

	cmd = *command;
	close(ex->fd2[0]);
	if (cmd->next && cmd->redir_out != 1 && cmd->dredir_out != 1)
		dup2(ex->fd2[1], 1);
	close(ex->fd2[1]);
	if (cmd->args[0] != NULL && command_check(&cmd, envex) == 1)
	{
		search_exec_2(&cmd, envex);
		if (execve(cmd->exec_path, cmd->args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	exit(0);
}

void	parent_ex(t_command **command, t_exec *ex, t_env **envex)
{
	t_command	*cmd;

	cmd = *command;
	close(ex->fd2[1]);
	if (cmd->next)
		dup2(ex->fd2[0], 0);
	close(ex->fd2[0]);
	fill_ter(cmd->args, envex, 1);
}

void	waiter(t_exec *ex)
{
	ex->i = 0;
	while (ex->i < ex->len)
	{
		waitpid(ex->pid[(ex->i)], &ex->status, 0);
		ex->i++;
	}
	free(ex->pid);
	ex->pid = NULL;
	(exit_status(ex->status >> 8), g_catch = 1);
}

void	execution_cmd(t_command **command, char **env, t_env **envex)
{
	t_exec		ex;
	t_command	*commands;

	ft_memset(&ex, 0, sizeof(t_exec));
	(1) && (commands = *command, ex.len = ft_lstsize_ex(commands));
	ex.pid = malloc(sizeof(int) * ex.len + 1);
	if (!ex.pid)
		malloc_fail();
	(1) && (ex.j = dup(1), ex.n = dup(0), ex.i = 0);
	while (commands != NULL)
	{
		ex_cmd(&commands, &ex, envex);
		if (pipe(ex.fd2) == -1)
			return (perror("pipe"));
		(ex.pid[ex.i] = fork());
		if (ex.pid[ex.i] == -1)
			return (perror("fork"));
		if (ex.pid[ex.i] == 0)
			child_ex(&commands, &ex, envex, env);
		else
			parent_ex(&commands, &ex, envex);
		(1) && (commands = commands->next, ex.i++);
	}
	(dup2(ex.j, 1), dup2(ex.n, 0), close(ex.j), close(ex.n));
	waiter(&ex);
}
