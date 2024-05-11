/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:36:47 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/10 19:16:05 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env **envex)
{
	t_env	*env;

	env = *envex;
	while (env)
	{
		if (env->q == 1 && env->vari != NULL && env->value != NULL)
		{
			// printf("here-> %s\n",env->value);
			printf("%s=%s\n", env->vari, env->value);
		}
		env = env->next;
	}
}
