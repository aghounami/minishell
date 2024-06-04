/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:19:28 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 12:28:46 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler_her(int signo)
{
	if (signo == SIGINT)
	{
		if (waitpid(-1, 0, WNOHANG) == 0)
		{
			printf("\n");
			exit_status(1);
			g_catch = 1;
			return ;
		}
		else
			exit(1);
	}
}

int	redire_2(int fd, int *flag, char *str, int file)
{
	if (fd == -1)
	{
		exit_status(1);
		return (-1);
	}
	if (dup2(fd, file) == -1)
	{
		perror("Error Redirection");
		return (-1);
	}
	if (str)
		close(fd);
	*flag = 1;
	return (fd);
}

int	redire_3(t_command **command, int *i)
{
	t_command	*cmd;
	int			fd;

	fd = 0;
	cmd = *command;
	cmd->redir_out = 0;
	cmd->dredir_out = 0;
	if (ft_strncmp(cmd->rdrect[(*i)], ">", 2) == 0)
	{
		fd = open(cmd->rdrect[++(*i)], O_RDWR | O_CREAT | O_TRUNC, 0644);
		fd = redire_2(fd, &cmd->redir_out, cmd->rdrect[(*i) + 1], 1);
	}
	else if (ft_strncmp(cmd->rdrect[(*i)], ">>", 3) == 0)
	{
		fd = open(cmd->rdrect[++(*i)], O_RDWR | O_CREAT | O_APPEND, 0644);
		fd = redire_2(fd, &cmd->dredir_out, cmd->rdrect[(*i) + 1], 1);
	}
	return (fd);
}

void	herdoc_exe(int fd, int *i)
{
	(*i)++;
	dup2(fd, 0);
	close(fd);
	exit_status(1);
}

int	redire(t_command **command)
{
	t_command	*cmd;
	int			i;
	int			fd;

	cmd = *command;
	cmd->redir_in = 0;
	cmd->here_doc = 0;
	i = 0;
	fd = 0;
	while (cmd->rdrect[i])
	{
		if (ft_strncmp(cmd->rdrect[i], "<<", 3) == 0)
			herdoc_exe(cmd->fd, &i);
		else if (ft_strncmp(cmd->rdrect[i], "<", 2) == 0)
		{
			fd = open(cmd->rdrect[++i], O_RDONLY, 0644);
			fd = redire_2(fd, &cmd->redir_in, cmd->rdrect[i + 1], 0);
		}
		else
			fd = redire_3(command, &i);
		i++;
	}
	return (fd);
}
