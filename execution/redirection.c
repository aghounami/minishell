/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:11 by zaki              #+#    #+#             */
/*   Updated: 2024/05/05 10:16:54 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redire_in(t_command **command)
{
    t_command *cmd;

    cmd = *command;
    
    if (cmd->args[2] == NULL) 
        fprintf(stderr, "Usage: redire_out <filename>\n");
    int fd = open(cmd->args[2], O_RDONLY);
    if (fd == -1)
        perror("error open");
    if(dup2(fd, 0) == -1)
        perror("Error Redirection");
    close(fd);
}


void redire_out(t_command **command)
{
    t_command *cmd;

    cmd = *command;
    if (cmd->args[2] == NULL) 
        perror("Error Redirect out");
    int fd = open(cmd->args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror("error opening file");
    if(dup2(fd, 1) == -1)
        perror("Error Redirection");
    close(fd);
    // if (close(fd) == -1)
    //     perror("close");
    // if (close(stdout_fd) == -1) 
    //     perror("close");

}
