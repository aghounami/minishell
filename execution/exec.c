/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/06 18:39:09 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_command **commands, int pid, t_env **envex, char **env)
{
	int	status;

	status = 0;
	if (command_check(commands, envex) == 0)
		return ;
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			search_exec_2(commands, envex);
			if (execve((*commands)->exec_path, (*commands)->args, env) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	(exit_status(status >> 8), g_catch = 1);
	return ;
}

void	fill_ter(char **str, t_env **envex, int l)
{
	t_env	*ev;
	int		i;

	ev = *envex;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] == 0)
			break ;
		i++;
	}
	while (ev)
	{
		if (strncmp(ev->vari, "_", ft_strlen(ev->vari)) == 0)
		{
			(free(ev->value), ev->value = NULL);
			if (str[i] && l == 0)
				ev->value = ft_strdup(str[i]);
			else if (l == 2)
				ev->value = ft_strdup("env");
			else
				ev->value = ft_strdup("");
		}
		ev = ev->next;
	}
}

void	refiller2(t_env **envex, t_exec *ex, char **env, int a)
{
	t_env	*enve;

	enve = *envex;
	a = 0;
	ex->i = 0;
	while (env[ex->i])
	{
		free(env[ex->i]);
		env[ex->i] = NULL;
		ex->i++;
	}
	while (enve)
	{
		if (enve->q == 1 && enve->vari != NULL && enve->value != NULL)
			ex->i++;
		enve = enve->next;
	}
	ex->name2 = malloc(sizeof(char *) * (ex->i + 1));
	if (!ex->name2)
		(perror("refiller2"), exit(1));
	ex->i = 0;
}

char	**refiller(char **env, t_env **envex)
{
	t_env		*enve;
	t_exec		ex;
	static int	a = 0;

	ft_memset(&ex, 0, sizeof(t_exec));
	refiller2(envex, &ex, env, a);
	enve = *envex;
	while (enve)
	{
		if (enve->q == 1 && enve->vari != NULL && enve->value != NULL)
		{
			ex.new = ft_strjoin(enve->vari, "=");
			ex.tmp = ft_strjoin(ex.new, enve->value);
			free(ex.new);
			ex.name2[ex.i] = ft_strdup(ex.tmp);
			free(ex.tmp);
			ex.i++;
		}
		enve = enve->next;
	}
	ex.name2[ex.i] = NULL;
	(free(env), env = NULL, env = ex.name2);
	return (env);
}

char	**exec_check(t_command **command, char **env, int enp)
{
	static t_env	*envex;
	int				fd;

	ft_filler(&envex, env);
	if (envex != NULL)
		envex->empty = enp;
	(*command)->ex = enp;
	(*command)->evr = env;
	fd = 0;
	if ((*command)->next == NULL)
	{
		fill_ter((*command)->args, &envex, 0);
		if ((*command)->rdrect)
			fd = redire(command);
		if (fd < 0)
			return (refiller(env, &envex));
		if (fd != 0)
			close (fd);
		one_cmd(command, 0, &envex, env);
		return (refiller(env, &envex));
	}
	execution_cmd(command, env, &envex);
	return (refiller(env, &envex));
}
