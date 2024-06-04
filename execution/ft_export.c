/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:51 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 15:46:53 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	v_check(char *str)
{
	t_exec	var;

	ft_memset(&var, 0, sizeof(var));
	if (ft_strchr(str, '='))
	{
		var.value = ft_strstr(str, "=") + 1;
		var.len = ft_strlen(str) - ft_strlen(var.value) - 1;
		var.vari = ft_substr(str, 0, var.len);
	}
	else
		var.vari = ft_strdup(str);
	if ((string_chcker(var.vari) && double_check(var.vari)))
	{
		free(var.vari);
		var.vari = NULL;
		return (1);
	}
	free(var.vari);
	var.vari = NULL;
	problem(str);
	return (0);
}

void	fc(char **value, char **vari, int *len, char *str)
{
	(*value) = ft_strdup(ft_strstr(str, "=") + 1);
	(*len) = ft_strlen(str) - ft_strlen((*value)) - 1;
	(*vari) = ft_substr(str, 0, (*len));
}

void	check_plus(t_exec **var, t_env **ev)
{
	(*var)->tmp = list_check(ev, (*var)->vari);
	(*var)->new = ft_strjoin((*var)->tmp, (*var)->value);
	(free((*var)->value), (*var)->value = NULL);
	(*var)->value = (*var)->new;
}

void	ft_ex_filler(char *str, t_exec *var, t_env **ev)
{
	if (ft_strchr(str, '='))
	{
		fc(&var->value, &var->vari, &var->len, str);
		if (var->vari[ft_strlen(var->vari) - 1] == '+')
		{
			var->tmp = var->vari;
			var->vari = ft_substr(str, 0, ft_strlen(var->vari) - 1);
			(free(var->tmp), var->tmp = NULL);
			if (list_check(ev, var->vari))
				check_plus(&var, ev);
		}
		if (!list_check(ev, var->vari))
			ft_lstadd_back_exec(ev, ft_lstnew_exec(var->value, var->vari, 1));
		else
			ft_adder(ev, var->vari, var->value);
	}
	else
	{
		if (cheking(str))
			return (problem(str));
		var->vari = ft_strdup(str);
		if (!list_check(ev, var->vari))
			ft_lstadd_back_exec(ev, ft_lstnew_exec("", var->vari, 0));
	}
	(free(var->value), var->value = NULL, free(var->vari), var->vari = NULL);
}

void	ft_export(t_command **command, t_env **envex)
{
	t_command	*exp;
	t_exec		var;
	int			f;

	ft_memset(&var, 0, sizeof(t_exec));
	exp = *command;
	f = 1;
	while (exp->args[f])
	{
		if (v_check(exp->args[f]))
			ft_ex_filler(exp->args[f], &var, envex);
		f++;
	}
	if (!exp->args[1])
		export_printer(envex);
}
