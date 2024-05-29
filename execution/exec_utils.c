/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:52:06 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/29 20:08:27 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char **env_hard(char **str)
// {
// 	char 
// 	int i =0;
// 	env = malloc(sizeof(char *) * (7 + 1));
	
// }
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
void pwd_update(t_env **env, char *str)
{
	t_env *envex;
	
	envex = *env;
	char *tmp = NULL;
	char *tmp2 = NULL;
	while(envex)
	{
		if (ft_strncmp(envex->vari, str, 4) == 0)
		{
			tmp =  ft_strdup(envex->value);
			free(envex->value);
			envex->value = ft_strdup(getcwd(tmp2, PATH_MAX));
		}
		envex = envex->next;
	}
	if (tmp)
		(free(tmp), tmp = NULL);
	if (tmp2)
		(free(tmp2), tmp2 = NULL);
	
}
void	ft_filler(t_env **env, char **envar)
{
	t_env *envex;
	t_exec		var;
	static int a ;
	
	envex = *env;
	ft_memset(&var, 0, sizeof(var));
	if(!envex && a == 0)
	{
		while(envar[var.i])
		{
			if (ft_strchr(envar[var.i], '='))
			{
				var.value = ft_strstr(envar[var.i], "=") + 1;
				var.len = ft_strlen(envar[var.i]) - ft_strlen(var.value) - 1;
				var.vari = ft_substr(envar[var.i], 0 ,var.len);
			}
			else
				var.vari = ft_substr(envar[var.i], 0 , ft_strlen(envar[var.i]));
			if(!envex)
				envex = ft_lstnew_exec(var.value, var.vari, 1);
			else
				ft_lstadd_back_exec(&envex, ft_lstnew_exec(var.value, var.vari, 1));
			var.i++;
		}

	a = 1;
	*env = envex;
	}
}
int ret(t_command **command)
{
	t_command	*exec;
	
	exec = *command;
	return(exec->redir_out ||exec->dredir_out ||exec->redir_in);
}
int	command_check(t_command **command, t_env **envex)
{
	t_command	*exec;
	
	exec = *command;
	exit_status(0);
	if (!exec->args[0])
		return(0);
	else if (!ft_strncmp("cd", exec->args[0], 3))
		return (cd_checker(command, envex), 0);
	else if (!ft_strncmp("echo", exec->args[0], 5)
		|| !ft_strncmp("ECHO", exec->args[0], 5))
		return (ft_echo(command), 0);
	else if (!ft_strncmp("export", exec->args[0], 7))
		return (ft_export(command, envex), 0);
	else if (!ft_strncmp("pwd", exec->args[0], 4)
		|| !ft_strncmp("PWD", exec->args[0], 4))
		return (ft_pwd(), 0);
	else if (!ft_strncmp("unset", exec->args[0], 6))
		return (ft_unset(command,envex), 0);
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

