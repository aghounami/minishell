/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:36:47 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 16:10:07 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env **envex)
{
	t_env	*env;
	int		a;

	env = *envex;
	if (env == NULL)
	{
		(exit_status(127), er_print("env", ": No such file or directory\n", 1));
		return ;
	}
	a = env->empty;
	while (env)
	{
		if (env->q == 1 && env->vari != NULL && env->value != NULL)
		{
			if (a == 0)
				printf("%s=%s\n", env->vari, env->value);
			else
			{
				if (ft_strncmp("PATH", env->vari, ft_strlen(env->vari)) != 0)
					printf("%s=%s\n", env->vari, env->value);
			}
		}
		env = env->next;
	}
}
