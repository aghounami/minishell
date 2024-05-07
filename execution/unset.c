/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:00:02 by hel-magh          #+#    #+#             */
/*   Updated: 2024/04/30 11:27:10 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void ft_unset(t_command **command, t_env **envexx)
{
    t_env *env;
    t_env *prev;
    t_env *tmp;
    t_exec var;
    t_command *unset;
	
	if (!*envexx)
		return;
	unset = *command;
    
	int f = 1;
	while (unset->args[f])
	{
		prev = NULL;
		env = *envexx;
		while (env)
		{
			var.vari = unset->args[f];
			if (ft_strncmp(env->vari, var.vari, ft_strlen(var.vari)) == 0)
			{
				if (prev == NULL)
					*envexx = env->next;
				else
					prev->next = env->next;
				free(env->vari);
				free(env->value);
				tmp = env;
				env = env->next;
				free(tmp);
				tmp = NULL;
			}
			else
			{
				prev = env;
				env = env->next;
			}
		}
		f++;
	}
}