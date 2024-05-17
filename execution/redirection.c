/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:11 by zaki              #+#    #+#             */
/*   Updated: 2024/05/16 20:05:34 by aghounam         ###   ########.fr       */
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
    int r = dup(0);
    cmd->dredir_out = 0;
    cmd->redir_in = 0;
    cmd->redir_out = 0;
    cmd->here_doc = 0;
    char *temp_filename = "/tmp/here_doc.txt";
    while (cmd->rdrect[i])
     {
      if (ft_strncmp(cmd->rdrect[i], "<<", 3) == 0) 
      {
            dup2(r, 0);
            i++;
            char *delimiter = cmd->rdrect[i];
            unlink(temp_filename);
            int fd2 = open(temp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
            fd = open(temp_filename, O_RDONLY);
            unlink(temp_filename);
           
            char *line = NULL;
            while ((line = readline("> ")) != NULL) {
                if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
                {
                    free(line);
                    break;
                }
                write(fd2, line, ft_strlen(line));
                write(fd2, "\n", 1);
                free(line);
            }
            
            close(fd2);

            dup2(fd, 0);
            close(fd);
            
            cmd->here_doc = 1;
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
                // close(0);
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
             if (fd == -1) {
                 perror(cmd->rdrect[i]);
                 return -1;
             }
             if (dup2(fd, 1) == -1) {
                 perror("Error Redirection");
                 return -1;
             }
             if (cmd->rdrect[i + 1])
                 close(fd);
                cmd->dredir_out = 1;
        }
        

        i++;
    }
    return(fd);
}
