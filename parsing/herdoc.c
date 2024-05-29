/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:47:57 by aghounam          #+#    #+#             */
/*   Updated: 2024/05/29 12:43:47 by aghounam         ###   ########.fr       */
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

int	herdoc(t_command **command, char **envp, int i, int pid)
{
	t_command	*cmd;
	t_elem		*elem;
	char		*line;
	int			fd2;

	cmd = *command;
	i = 0;
	cmd->here_doc = 0;
	while (cmd->rdrect[i] && cmd->hrdoc_nbr > 0)
	{
		if (catch == 1)
			break ;
		if (ft_strncmp(cmd->rdrect[i], "<<", 3) == 0)
		{
			cmd->hrdoc_nbr -= 1;
			i++;
			if (cmd->rdrect[i] == NULL)
				break ;
			unlink("/tmp/.tmpfile");
			fd2 = open("/tmp/.tmpfile", O_CREAT | O_WRONLY | O_TRUNC, 0600);
			cmd->fd = open("/tmp/.tmpfile", O_RDONLY);
			unlink("/tmp/.tmpfile");
			pid = fork();
			if (pid == 0)
			{
				rl_catch_signals = 1;
				signal(SIGINT, sig_handler_her);
				signal(SIGQUIT, SIG_IGN);
				while (1)
				{
					elem = NULL;
					line = readline("> ");
					if (!line || (ft_strncmp(line, cmd->rdrect[i], \
						ft_strlen(cmd->rdrect[i])) == 0 \
							&& ft_strlen(line) == ft_strlen(cmd->rdrect[i])))
					{
						free(line);
						close(fd2);
						exit(0);
					}
					if (line && line[0] != '\0' && cmd->check_expand == 0)
					{
						lexer(line, &elem, envp, 1);
						state(&elem, envp, 1);
						line = NULL;
						over_write(&elem, &line);
					}
					write(fd2, line, ft_strlen(line));
					write(fd2, "\n", 1);
					free(line);
				}
				close(fd2);
			}
			else
			{
				waitpid(pid, 0, 0);
				close(fd2);
				cmd->here_doc = 1;
			}
		}
		i++;
	}
	return (0);
}

void	open_herdoc(t_command **command, char **envp, int *nbr_hdoc)
{
	t_command	*cmd;

	cmd = *command;
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
