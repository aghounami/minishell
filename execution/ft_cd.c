/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/06 17:24:14 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_path_join(t_command **cmd, t_exec *d_cd, t_env **envex)
{
	t_command	*exec;
	t_exec		*cd;

	exec = *cmd;
	cd = d_cd;
	cd->t_path = ft_strdup(cd->current_dir);
	if (exec->args[1] != NULL && ft_strncmp(exec->args[1], "~", 2)
		&& ft_strncmp(exec->args[1], "~/", 2) && exec->args[1][0] != '/')
	{
		cd->tmp = cd->current_dir;
		cd->current_dir = ft_strjoin(cd->tmp, "/");
		if (!cd->current_dir)
			ft_exit_fail("cd->current_dir_cd");
		(free(cd->t_path), cd->t_path = NULL, free(cd->tmp), cd->tmp = NULL);
		cd->t_path = ft_strjoin(cd->current_dir, exec->args[1]);
		if (!cd->t_path)
			ft_exit_fail("Path problem_cd");
	}
	if (cd_dir(cd->t_path))
		cd_changer(cd->t_path, envex);
	else if (cd->t_path)
		error_printer(exec->args[1], ": No such file or directory\n", 1);
	(free(cd->t_path), free(cd->current_dir));
}

void	env_get(char *str, t_env **envex)
{
	t_env	*ev;
	char	*tmp;

	ev = *envex;
	tmp = NULL;
	while (ev)
	{
		if (ft_strncmp(ev->vari, str, ft_strlen(ev->value)) == 0 \
			&& ft_strlen(str) == ft_strlen(ev->vari))
		{
			tmp = ev->value;
			ev->value = ft_strjoin(tmp, "/..");
			(free(tmp), tmp = NULL);
		}
		ev = ev->next;
	}
}

void	cd_checker(t_command **command, t_env **envex)
{
	t_command	*exec;
	t_exec		cd;

	ft_memset(&cd, 0, sizeof(cd));
	exec = *command;
	cd.current_dir = getcwd(NULL, PATH_MAX);
	if (exec->args[1] == NULL)
	{
		(free(cd.current_dir));
		return ;
	}
	if (cd_dir(exec->args[1]))
	{
		if (cd.current_dir != NULL)
			(cd_changer(exec->args[1], envex), free(cd.current_dir), \
			cd.current_dir = NULL);
		else
			cd_handler(exec->args[1], envex, &cd);
	}
	else if (cd.current_dir != NULL)
		cd_path_join(command, &cd, envex);
}
