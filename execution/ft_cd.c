/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/30 04:59:56 by aghounam         ###   ########.fr       */
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

int	path_cheker_cd(char *path)
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
			printf("path changed to %s\n", path);
			chdir(path);
		}
		return (1);
	}
	return (0);
}

int	getcwd_check(t_command **command, t_exec *dir_cd, char *path)
{
	// t_command	*exec;
	t_exec		*cd;

	// exec = *command;
	(void)command;
	cd = dir_cd;
	if (getcwd(cd->current_dir, PATH_MAX) == NULL)
	{
		path_cheker_cd(path);
		if (!cd_dir(path))
			perror("current dir problem_cd2");
		free(cd->current_dir);
		return (1);
	}
	return (0);
}

void	cd_path_join(t_command **command, t_exec *dir_cd, char *path)
{
	t_command	*exec;
	t_exec		*cd;

	exec = *command;
	cd = dir_cd;
	if (exec->args[1] != NULL && ft_strncmp(exec->args[1], "~", 2)
		&& ft_strncmp(exec->args[1], "~/", 2))
	{
		cd->current_dir = ft_strjoin(cd->current_dir, "/");
		if (!cd->current_dir)
			ft_exit_fail("cd->current_dir_cd");
		path = ft_strjoin(cd->current_dir, exec->args[1]);
		if (!path)
			ft_exit_fail("Path problem_cd");
	}
	else if (exec->args[1] == NULL || (exec->args[1] != NULL
			&& !ft_strncmp(exec->args[1], "~", 2)))
		path = getenv("HOME");
	if (cd_dir(path))
	{
		printf("path changed to %s\n", path);
		chdir(path);
	}
	else
		printf("Is not a Directory -> path %s\n", path);
}

void	cd_checker(t_command **command)
{
	t_command	*exec;
	t_exec		cd;
	static char	*path;

	ft_memset(&cd, 0, sizeof(cd));
	exec = *command;
	cd.current_dir = (char *)malloc(PATH_MAX);
	if (!cd.current_dir)
		ft_exit_fail("current dir problem_cd");
	if (getcwd_check(command, &cd, path))
		return ;
	if (cd_dir(exec->args[1]))
	{
		chdir(exec->args[1]);
		getcwd(cd.current_dir, PATH_MAX);
		path = cd.current_dir;
		printf("path changed to this %s\n", path);
	}
	else
		cd_path_join(command, &cd, path);
	free(cd.current_dir);
}
