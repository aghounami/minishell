/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:41:51 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/06 17:01:09 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_env **env)
{
	char	*path;
	char	*content;

	path = NULL;
	content = (char *)malloc(PATH_MAX);
	if (!content)
		ft_exit_fail("pwd malloc");
	if (getcwd(content, PATH_MAX) != NULL)
		printf("%s\n", content);
	else
	{
		path = get_envx("PWD", env);
		if (path)
			printf("%s\n", path);
		else
			perror("pwd");
	}
	if (path)
		(free(path), path = NULL);
	if (content)
		(free(content), content = NULL);
}
