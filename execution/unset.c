/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:00:02 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/12 11:48:56 by hel-magh         ###   ########.fr       */
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
		if (string_chcker(unset->args[f]))
		{
			
		
			while (env)
			{
				var.vari = unset->args[f];
				if (ft_strncmp(env->vari, var.vari, ft_strlen(env->vari)) == 0)
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
		}
		else 
			printf("unset: `%s': not a valid identifier\n", unset->args[f]);
		f++;
	}
}