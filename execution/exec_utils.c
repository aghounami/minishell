/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:52:06 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/06 19:14:24 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rac(char **value, char **vari, int *len, char *str)
{
	(*value) = ft_strstr(str, "=") + 1;
	(*len) = ft_strlen(str) - ft_strlen((*value)) - 1;
	(*vari) = ft_substr(str, 0, (*len));
}

void	ft_filler(t_env **env, char **envar)
{
	t_env		*envex;
	t_exec		v;
	static int	a;

	envex = *env;
	ft_memset(&v, 0, sizeof(v));
	if (!envex && a == 0)
	{
		while (envar[v.i])
		{
			if (ft_strchr(envar[v.i], '='))
				rac(&v.value, &v.vari, &v.len, envar[v.i]);
			else
				v.vari = ft_substr(envar[v.i], 0, ft_strlen(envar[v.i]));
			if (!envex)
				envex = ft_lstnew_exec(v.value, v.vari, 1);
			else
				ft_lstadd_back_exec(&envex, ft_lstnew_exec(v.value, v.vari, 1));
			free(v.vari);
			v.i++;
		}
		a = 1;
		*env = envex;
	}
}

int	ret(t_command **command)
{
	t_command	*exec;

	exec = *command;
	return (exec->redir_out || exec->dredir_out || exec->redir_in);
}

int	command_check(t_command **command, t_env **envex)
{
	t_command	*exec;

	exec = *command;
	exit_status(0);
	if (!exec->args[0])
		return (0);
	else if (!ft_strncmp("cd", exec->args[0], 3))
		return (cd_checker(command, envex), 0);
	else if (!ft_strncmp("echo", exec->args[0], 5)
		|| !ft_strncmp("ECHO", exec->args[0], 5))
		return (ft_echo(command), 0);
	else if (!ft_strncmp("export", exec->args[0], 7))
		return (ft_export(command, envex), 0);
	else if (!ft_strncmp("pwd", exec->args[0], 4)
		|| !ft_strncmp("PWD", exec->args[0], 4))
		return (ft_pwd(envex), 0);
	else if (!ft_strncmp("unset", exec->args[0], 6))
		return (ft_unset(command, envex), 0);
	else if (!ft_strncmp("env", exec->args[0], 4)
		|| !ft_strncmp("ENV", exec->args[0], 4))
		return (ft_env(envex), 0);
	else if (!ft_strncmp("exit", exec->args[0], 5))
		return (ft_exit_mini(command), 0);
	return (1);
}

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s2[j] && s1[i + j] == s2[j])
			{
				j++;
			}
			if (s2[j] == '\0')
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
