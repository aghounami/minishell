/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:51:13 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/07 20:17:30 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_herdoc(t_command **command)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp)
	{
		if (tmp->fd != 0)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

void	expanding(char **line, char **envp, int *fd2, t_command *cmd)
{
	t_elem	*elem;

	elem = NULL;
	if (*line && *line[0] != '\0' && cmd->check_expand == 0)
	{
		lexer(*line, &elem, envp, 1);
		(1) && (state(&elem, envp, 1), free(*line), *line = NULL);
		over_write(&elem, line);
	}
	write(*fd2, *line, ft_strlen(*line));
	write(*fd2, "\n", 1);
	free(*line);
}

void	check_dlmtr(char **line, int fd2, t_command *cmd, int i)
{
	if (!(*line) || (ft_strncmp((*line), cmd->rdrect[i], \
		ft_strlen(cmd->rdrect[i])) == 0 \
			&& ft_strlen((*line)) == ft_strlen(cmd->rdrect[i])))
		(1) && (free((*line)), close(fd2), exit(0), (*line) = NULL);
}

void	empty_env(t_varr **var)
{
	(*var)->enp = 1;
	(*var)->envp = malloc(sizeof(char *) * 6);
	if (!(*var)->envp)
		malloc_fail();
	(*var)->envp[0] = ft_strdup("OLDPWD");
	(*var)->envp[1] = ft_strdup("PWD=/Users/hel-magh/Desktop/minishell");
	(*var)->envp[2] = ft_strdup("SHLVL=1");
	(*var)->envp[3] = ft_strdup("_=/usr/bin/env");
	(*var)->envp[4] = ft_strdup("PATH=/Users/hel-magh/.brew/bin:/usr/local/bin:"
			"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:"
			"/Library/Apple/usr/bin:/Users/hel-magh/.brew/bin");
	(*var)->envp[5] = NULL;
}
