/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:29:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/05 16:36:15 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_changer(char **path, t_env **envex)
{
	pwd_update(envex, "OLDPWD");
	chdir(*path);
	pwd_update(envex, "PWD");
}

void	error_printer(char *str, char *str2, int i)
{
	exit_status(i);
	ft_putstr_fd("minishell: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
}

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
			error_printer(exec->args[1], ": No such file or directory\n", 1);
		else
			chdir(path);
		return (1);
	}
	return (0);
}
