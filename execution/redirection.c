/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:11 by zaki              #+#    #+#             */
/*   Updated: 2024/05/13 21:43:35 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int redire_in(t_command **command) {
//     t_command *cmd = *command;
//     int i = 0;
//     int fd;

//     while (cmd->rd_in[i]) 
//     {
//         if (ft_strncmp(cmd->rd_in[i], "<", 2) == 0)
//          {
//             i++;
//             fd = open(cmd->rd_in[i], O_RDONLY, 0644);
//             if (fd == -1)
//              {
//                 perror(cmd->rd_in[i]);
//                 return -1;
//             }
//             if (dup2(fd, 0) == -1) 
//             {
//                 perror("Error Redirection");
//                 return -1;
//             }
//             if (cmd->rd_in[i + 1])
//                 close(fd); 
//         }
//         i++;
//     }
// return(fd);
// }


int redire(t_command **command) {
    t_command *cmd = *command;
    int i = 0;
    int fd =0;

    cmd->dredir_out = 0;
    cmd->redir_in = 0;
    cmd->redir_out = 0;
    while (cmd->redirection[i])
     {
         if (ft_strncmp(cmd->redirection[i], "<", 2) == 0)
         {
            i++;
            fd = open(cmd->redirection[i], O_RDONLY, 0644);
            if (fd == -1)
             {
                perror(cmd->redirection[i]);
                return -1;
            }
            if (dup2(fd, 0) == -1) 
            {
                perror("Error Redirection");
                return -1;
            }
            if (cmd->redirection[i + 1])
                close(fd); 
            cmd->redir_in = 1;
        }
        if (ft_strncmp(cmd->redirection[i], ">", 2) == 0) 
        {
            i++;
            fd = open(cmd->redirection[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) 
            {
                perror(cmd->redirection[i]);
                return -1;
            }
                // close(0);
                if (dup2(fd, 1) == -1) 
                {
                    perror("Error Redirection");
                    return -1;
                }
                if (cmd->redirection[i + 1])
                    close(fd);
            cmd->redir_out = 1;
            
           
        }
        else if (ft_strncmp(cmd->redirection[i], ">>", 3) == 0) 
        {
            i++;
             fd = open(cmd->redirection[i], O_RDWR | O_CREAT | O_APPEND, 0644);
             if (fd == -1) {
                 perror(cmd->redirection[i]);
                 return -1;
             }
             if (dup2(fd, 1) == -1) {
                 perror("Error Redirection");
                 return -1;
             }
             if (cmd->redirection[i + 1])
                 close(fd);
                cmd->dredir_out = 1;
        }
        i++;
    }
    return(fd);
}

