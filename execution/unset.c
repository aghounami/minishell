/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:00:02 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 12:59:48 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheking(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	problem(char *str)
{
	exit_status(1);
	ft_putstr_fd("minishell: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	string_chcker_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		while (str[i])
		{
			if (ft_isalpha(str[i]) || ft_isdigit(str[i])
				|| str[i] == '_')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_unset_2(t_env **ev, t_exec *var, t_env **envex, char *str)
{
	t_env		*tmp;
	t_env		*env;
	t_env		*prev;

	env = *ev;
	prev = NULL;
	while (env)
	{
		var->vari = str;
		if (ft_strncmp(env->vari, var->vari, ft_strlen(env->vari)) == 0)
		{
			if (prev == NULL)
				*envex = env->next;
			else
				prev->next = env->next;
			(free(env->vari), free(env->value), tmp = env);
			env = env->next;
			(free(tmp), tmp = NULL);
		}
		else
		{
			prev = env;
			env = env->next;
		}
	}
}

void	ft_unset(t_command **command, t_env **envexx)
{
	t_env		*env;
	t_exec		var;
	t_command	*unset;

	unset = *command;
	ft_memset(&var, 0, sizeof(t_exec));
	if (!*envexx && unset->args[0] != NULL)
		return ;
	var.j = 1;
	while (unset->args[var.j])
	{
		env = *envexx;
		if (string_chcker_unset(unset->args[var.j]))
			ft_unset_2(&env, &var, envexx, unset->args[var.j]);
		else
			error_printer(unset->args[var.j], "': not a valid identifier\n", 1);
		var.j++;
	}
}
