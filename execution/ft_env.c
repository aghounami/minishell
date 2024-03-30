/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:36:47 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/30 01:09:24 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_command **command)
{
	t_command	*env;
	int			i;

	env = *command;
	i = 0;
	if (env->args[1] == NULL)
	{
		while (env->env[i] != NULL)
		{
			printf("%s\n", env->env[i]);
			i++;
		}
	}
	else
		return ;
}
