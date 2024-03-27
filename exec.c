/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:58:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/03/27 15:58:44 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_path(t_command **command)
{
	t_command	*exec;
	char		*path_in;
	char		*path;

	exec = *command;
	path_in = "/bin/";
	path = ft_strjoin(path_in, exec->args[0]);
	if (!path)
		printf("path problem\n");
	if (execve((const char *)path, (char *const *)exec->args, NULL) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	exec_check(t_command **command)
{
	int		state;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_path(command);
	else if (pid > 0)
	{
		if (waitpid(0, &state, 0) == -1)
			perror("waitpid");
	}
	else
		perror("fork");
}
