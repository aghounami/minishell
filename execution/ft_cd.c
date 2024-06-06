/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/05 16:29:21 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_path_join(t_command **cmd, t_exec *d_cd, char **path, t_env **envex)
{
	t_command	*exec;
	t_exec		*cd;

	exec = *cmd;
	cd = d_cd;
	cd->t_path = ft_strdup(*path);
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
		cd_changer(path, envex);
	else if (cd->t_path)
		error_printer(exec->args[1], ": No such file or directory\n", 1);
	(free(cd->t_path), free(cd->current_dir));
}

void	cd_checker(t_command **command, t_env **envex)
{
	t_command	*exec;
	t_exec		cd;
	static char	*path;

	ft_memset(&cd, 0, sizeof(cd));
	exec = *command;
	cd.current_dir = (char *)malloc(PATH_MAX);
	if (!cd.current_dir)
		ft_exit_fail("current dir problem_cd");
	if (exec->args[1] == NULL || getcwd_check(command, &cd, path, envex))
	{
		(free(cd.current_dir));
		return ;
	}
	if (cd_dir(exec->args[1]))
	{
		pwd_update(envex, "OLDPWD");
		chdir(exec->args[1]);
		pwd_update(envex, "PWD");
		getcwd(cd.current_dir, PATH_MAX);
		path = cd.current_dir;
		free(cd.current_dir);
	}
	else
		cd_path_join(command, &cd, &path, envex);
}
