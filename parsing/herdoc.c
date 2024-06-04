/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:47:57 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/04 16:36:51 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	wait_herdoc(int pid, int fd2, t_command **cmd)
{
	waitpid(pid, 0, 0);
	close(fd2);
	(*cmd)->here_doc = 1;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

int	init_child(int *fd2, t_command **cmd, int *i)
{
	int	pid;

	(1) && ((*cmd)->hrdoc_nbr -= 1, *i += 1);
	unlink("/tmp/.tmpfile");
	*fd2 = open("/tmp/.tmpfile", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if ((*cmd)->fd != 0)
		close((*cmd)->fd);
	(*cmd)->fd = open("/tmp/.tmpfile", O_RDONLY);
	unlink("/tmp/.tmpfile");
	rl_catch_signals = 1;
	signal(SIGINT, sig_handler_her);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	return (pid);
}

int	herdoc(t_command **command, char **envp, int i, int pid)
{
	t_command	*cmd;
	char		*line;
	int			fd2;

	(1) && (cmd = *command, i = -1, cmd->here_doc = 0);
	while (cmd->rdrect[++i] && cmd->hrdoc_nbr > 0 && g_catch != 1)
	{
		if (ft_strncmp(cmd->rdrect[i], "<<", 3) == 0 && cmd->rdrect[i + 1])
		{
			pid = init_child(&fd2, &cmd, &i);
			if (pid == 0)
			{
				while (1)
				{
					line = readline(" > ");
					check_dlmtr(&line, fd2, cmd, i);
					expanding(&line, envp, &fd2, cmd);
				}
			}
			else
				wait_herdoc(pid, fd2, &cmd);
		}
	}
	return (0);
}

void	open_herdoc(t_command **command, char **envp, int *nbr_hdoc)
{
	t_command	*cmd;

	cmd = *command;
	if (cmd == NULL || cmd->rdrect == NULL)
		return ;
	cmd->fd = 0;
	while (cmd)
	{
		cmd->hrdoc_nbr = *nbr_hdoc;
		herdoc(&cmd, envp, 0, 0);
		if (cmd->fd == -1)
			break ;
		if (cmd->hrdoc_nbr <= 0)
			break ;
		cmd = cmd->next;
	}
}
