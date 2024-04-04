/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:36:47 by hel-magh          #+#    #+#             */
/*   Updated: 2024/04/02 14:05:10 by hel-magh         ###   ########.fr       */
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
		while (env->evr[i] != NULL )
		{
				printf("%s\n", env->evr[i]);
			i++;
		}
	}
	else
		return ;
}
