/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/29 15:34:47 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_dir(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (0);
	return (S_ISDIR(info.st_mode));
}

int	path_cheker_cd(char *path, t_env **envex)
{
	int	i;
	 
	i = 0;
	if (path)
	{
		i = ft_strlen(path);
		while (i > 0)
		{
			if (path[i] == '/')
				break ;
			i--;
		}
		if (path[i] == '/')
			path[i] = '\0';
		if (cd_dir(path))
		{
			pwd_update(envex, "OLDPWD");
			printf("path changed to here -> 3 %s\n", path);
			pwd_update(envex, "PWD");
		}
		return (1);
	}
	return (0);
}

int	getcwd_check(t_command **command, t_exec *dir_cd, char *path, t_env **envex)
{
	t_command	*exec;
	t_exec		*cd;

	exec = *command;
	cd = dir_cd;
	if (getcwd(cd->current_dir, PATH_MAX) == NULL)
	{
		path_cheker_cd(path, envex);
		if (!cd_dir(path))
			perror("current dir problem_cd2");
		free(cd->current_dir);
		return (1);
	}
	return (0);
}

void	cd_path_join(t_command **command, t_exec *dir_cd, char *path, t_env **envex)
{
	t_command	*exec;
	t_exec		*cd;

	exec = *command;
	cd = dir_cd;
	if (exec->args[1] != NULL && ft_strncmp(exec->args[1], "~", 2)
		&& ft_strncmp(exec->args[1], "~/", 2) && exec->args[1][0] != '/')
	{
		cd->current_dir = ft_strjoin(cd->current_dir, "/");
		if (!cd->current_dir)
			ft_exit_fail("cd->current_dir_cd");
		path = ft_strjoin(cd->current_dir, exec->args[1]);
		if (!path)
			ft_exit_fail("Path problem_cd");
	}
	else if ((exec->args[1] != NULL
			&& !ft_strncmp(exec->args[1], "~", 2)))
		path = getenv("HOME");
	if (cd_dir(path))
	{
		pwd_update(envex, "OLDPWD");
		printf("path changed to this here->2 %s\n", path);
		chdir(path);
		pwd_update(envex, "PWD");
	}
	else if (path)
	{
		exit_status(1);
		printf("minishell: cd: %s: No such file or directory\n", exec->args[1]);
	}
}

void	cd_checker(t_command **command, t_env **envex)
{
	t_command	*exec;
	t_exec		cd;
	static char	*path;

	ft_memset(&cd, 0, sizeof(cd));
	exec = *command;
	if (exec->args[1] == NULL)
		return;
	cd.current_dir = (char *)malloc(PATH_MAX);
	if (!cd.current_dir)
		ft_exit_fail("current dir problem_cd");
	if (getcwd_check(command, &cd, path, envex))
	{
		(free(path), free(cd.current_dir));
		return ;
	}
	if (cd_dir(exec->args[1]))
	{
		pwd_update(envex, "OLDPWD");
		chdir(exec->args[1]);
		getcwd(cd.current_dir, PATH_MAX);
		path = cd.current_dir;
		pwd_update(envex, "PWD");
		printf("path changed to this here1 ->%s\n", path);
	}
	else
		cd_path_join(command, &cd, path, envex);
	free(cd.current_dir);
}
