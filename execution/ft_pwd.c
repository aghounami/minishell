/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:41:51 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/30 05:00:05 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char		*content;
	static char	*path;
	static int	i;

	content = (char *)malloc(PATH_MAX);
	if (!content)
		ft_exit_fail("pwd malloc");
	if (getcwd(content, PATH_MAX) != NULL)
	{
		printf("%s\n", content);
		path = content;
		free(content);
		i = 0;
	}
	else
	{
		if (i == 0)
		{
			i = 1 ;
			printf("%s\n", path);
		}
		else
			perror("getcwd");
	}
}
