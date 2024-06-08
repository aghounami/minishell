/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:29:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/06 17:21:23 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_changer(char *path, t_env **envex)
{
	pwd_update(envex, "OLDPWD");
	chdir(path);
	pwd_update(envex, "PWD");
}

void	error_printer(char *str, char *str2, int i)
{
	exit_status(i);
	ft_putstr_fd("minishell: `", 2);
	if (str)
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

void	cd_handler(char *str, t_env **ev, t_exec *cd)
{
	static int	a = 0;

	(free(cd->current_dir));
	env_get("PWD", ev);
	chdir(str);
	cd->current_dir = getcwd(cd->current_dir, PATH_MAX);
	if (cd->current_dir == NULL && a > 0)
		perror("getcwd");
	else if (a == 0)
		error_printer(NULL, ": No such file or directory\n", 0);
	(free(cd->current_dir));
	a = 1;
}
