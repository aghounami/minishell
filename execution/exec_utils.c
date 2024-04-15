/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:52:06 by hel-magh          #+#    #+#             */
/*   Updated: 2024/04/14 23:07:49 by aghounam         ###   ########.fr       */
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
	while (invar->evr[inv.index])
	{
		if (ft_strncmp(invar->evr[inv.index], inv.name,
				ft_strlen(inv.name)) == 0
			&& invar->evr[inv.index][ft_strlen(inv.name)] == '=')
		{
			while (invar->evr[inv.index][inv.j] != '=')
				inv.j++;
			inv.value = ft_strdup(invar->evr[inv.index] + inv.j + 1);
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
	// t_env		*env;
	
	exec = *command;
	if (!ft_strncmp("cd", exec->args[0], 3))
		return (cd_checker(command), 0);
	else if (!ft_strncmp("echo", exec->args[0], 5)
		|| !ft_strncmp("ECHO", exec->args[0], 5))
		return (ft_echo(command), 0);
	else if (!ft_strncmp("export", exec->args[0], 7)
		|| !ft_strncmp("EXPORT", exec->args[0], 7))
		return (ft_export(command), 0);
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

