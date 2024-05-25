/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:11 by zaki              #+#    #+#             */
/*   Updated: 2024/05/25 17:17:25 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void sig_handler_her(int signo)
// {
// 	if (signo == SIGINT)
// 	{
		
// 			printf("\n");
// 			exit(1);
		
// 	}
// }
int redire(t_command **command)
{
    t_command *cmd = *command;
    int i = 0;
    int fd = 0;
    cmd->dredir_out = 0;
    cmd->redir_in = 0;
    cmd->redir_out = 0;
    cmd->here_doc = 0;
   
    while (cmd->rdrect[i])
    {
      if (ft_strncmp(cmd->rdrect[i], "<<", 3) == 0)
      {
        fprintf(stderr, "here ---> %d\n", cmd->fd);
        dup2(cmd->fd, 0); // ba3ed may9adha parsser;
        close(cmd->fd);
        // fd = herdoc(command);
      }
      else if (ft_strncmp(cmd->rdrect[i], "<", 2) == 0)
        {
            i++;
            fd = open(cmd->rdrect[i], O_RDONLY, 0644);
            if (fd == -1)
            {
                perror(cmd->rdrect[i]);
                return -1;
            }
            if (dup2(fd, 0) == -1)
            {
                perror("Error Redirection");
                return -1;
            }
            if (cmd->rdrect[i + 1])
                close(fd);
            cmd->redir_in = 1;
        }
        else if (ft_strncmp(cmd->rdrect[i], ">", 2) == 0)
        {
            i++;
            fd = open(cmd->rdrect[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror(cmd->rdrect[i]);
                return -1;
            }
            if (dup2(fd, 1) == -1)
            {
                perror("Error Redirection");
                return -1;
            }
            if (cmd->rdrect[i + 1])
                close(fd);
            cmd->redir_out = 1;
        }
        else if (ft_strncmp(cmd->rdrect[i], ">>", 3) == 0)
        {
            i++;
            fd = open(cmd->rdrect[i], O_RDWR | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror(cmd->rdrect[i]);
                return -1;
            }
            if (dup2(fd, 1) == -1)
            {
                perror("Error Redirection");
                return -1;
            }
            if (cmd->rdrect[i + 1])
                close(fd);
            cmd->dredir_out = 1;
        }

        i++;
    }
    // close(r);
    return (fd);
}
