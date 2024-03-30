/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:52:06 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/30 04:59:40 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_exec(t_command **command)
{
	t_exec		inv;
	t_command	*invar;

	invar = *command;
	ft_memset(&inv, 0, sizeof(inv));
	inv.name = malloc(sizeof(char) * 100);
	inv.value = malloc(sizeof(char) * 100);
	inv.name = ft_strdup(invar->content);
	inv.value = NULL;
	while (invar->env[inv.index])
	{
		if (ft_strncmp(invar->env[inv.index], inv.name, ft_strlen(inv.name)) == 0
			&& invar->env[inv.index][ft_strlen(inv.name)] == '=')
		{
			while (invar->env[inv.index][inv.j] != '=')
				inv.j++;
			inv.value = ft_strdup(invar->env[inv.index] + inv.j + 1);
			break ;
		}
		inv.index++;
	}
	return (inv.value);
}

void	ft_free_double(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_exit_fail(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	command_check(t_command **command)
{
	t_command	*exec;

	exec = *command;
	if (!ft_strncmp("cd", exec->args[0], 3)
		||!ft_strncmp("CD", exec->args[0], 3))
		return (cd_checker(command), 0);
	else if (!ft_strncmp("echo", exec->args[0], 5)
		|| !ft_strncmp("ECHO", exec->args[0], 5))
		return (printf("it's echo\n"), 0);
	// else if (!ft_strncmp("export", exec->args[0], 7)
	// 	|| !ft_strncmp("EXPORT", exec->args[0], 7))
	// 	return (ft_export(command), 0);
	else if (!ft_strncmp("pwd", exec->args[0], 4)
		|| !ft_strncmp("PWD", exec->args[0], 4))
		return (ft_pwd(), 0);
	else if (!ft_strncmp("unset", exec->args[0], 6)
		|| !ft_strncmp("UNSET", exec->args[0], 6))
		return (printf("it's unset\n"), 0);
	else if (!ft_strncmp("env", exec->args[0], 4)
		|| !ft_strncmp("ENV", exec->args[0], 4))
		return (ft_env(command), 0);
	else if (!ft_strncmp("exit", exec->args[0], 5)
		|| !ft_strncmp("EXIT", exec->args[0], 5))
		return (ft_exit_mini(command), 0);
	return (1);
}
