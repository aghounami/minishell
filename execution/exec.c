/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:45 by hel-magh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/29 22:18:27 by aghounam         ###   ########.fr       */
=======
/*   Updated: 2024/05/28 16:00:27 by aghounam         ###   ########.fr       */
>>>>>>> b7f202203f5028a4ee0fa7d7f7650c343e1de6ba
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_extention(const char *p, char *const *ag, t_command **s)
{
	t_command	*exec;

	exec = *s;
	if (execve(p, ag, exec->evr) == -1)
	{
		printf("Error: %s: command not found\n", exec->args[0]);
		exit(EXIT_FAILURE);
	}
}

void	search_exec(t_command **command, t_exec *execution)
{
	t_command	*exec;
	t_exec		*p_exec;

	exec = *command;
	p_exec = execution;
	while (p_exec->path_split[p_exec->i])
	{
		p_exec->path = ft_strjoin(p_exec->path_split[p_exec->i], "/");
		if (!p_exec->path)
			ft_exit_fail("path problem");
		p_exec->exec_path = ft_strjoin(p_exec->path, exec->args[0]);
		if (!p_exec->exec_path)
			ft_exit_fail("exec path problem");
		if (access(p_exec->exec_path, X_OK) == 0)
		{
			free(p_exec->path);
			break ;
		}
		else
		{
			free(p_exec->path);
			free(p_exec->exec_path);
			p_exec->i++;
		}
	}
}

void	exec_path_extention(t_command **command, t_exec *execution)
{
	t_command	*exec;
	t_exec		*p_exec;

	exec = *command;
	p_exec = execution;
	search_exec(command, execution);
	free(p_exec->current_dir);
	ft_free_double(p_exec->path_split);
	exec_extention(p_exec->exec_path, exec->args, command);
}

void	exec_path(t_command **command)
{
	t_command	*exec;
	t_exec		p_exec;

	ft_memset(&p_exec, 0, sizeof(p_exec));
	exec = *command;
	(*command)->content = "PATH";
	p_exec.path_in = get_env_exec(command);
	p_exec.current_dir = (char *)malloc(PATH_MAX);
	if (!p_exec.current_dir || getcwd(p_exec.current_dir, PATH_MAX) == NULL)
		ft_exit_fail("current dir problem_exec");
	p_exec.path = ft_strjoin(p_exec.path_in, ":");
	if (!p_exec.path)
		ft_exit_fail("Path problem");
	p_exec.path = ft_strjoin(p_exec.path, p_exec.current_dir);
	if (!p_exec.path)
		ft_exit_fail("Path problem");
	p_exec.path_split = ft_split(p_exec.path, ':');
	if (!p_exec.path_split)
		ft_exit_fail("p_exec.Path_split problem");
	exec_path_extention(command, &p_exec);
}

void not_found(char *str)
{
	ft_putstr_fd("\033[0;31mminishell: \033[0m", 2);
		ft_putstr_fd("\033[0;31m command not found\033[0m: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
}
void search_exec_2(t_command **command, char **env)
{
	t_command *exec;
	t_exec *ex;
	int flag_access;
	
	(flag_access = 0, exec = *command);
	
	if (exec->args == NULL || exec->args[0] == NULL || exec->args[0][0] == '\0')
	{
		not_found(exec->args[0]);
		exit(1) ;
	}
	ex = malloc(sizeof(t_exec));
	if (!ex)
		ft_exit_fail("malloc failed");
	ex->path_split = ft_split(get_env("PATH", env), ':');
	if (!ex->path_split)
		ft_exit_fail("split failed");
	ex->i = 0;
	while (ex->path_split[ex->i])
	{
		if(!ft_isalpha(exec->args[0][1]))
			break;
		ex->path = ft_strjoin(ex->path_split[ex->i], "/");
		if (!ex->path)
			ft_exit_fail("path problem");
		ex->exec_path = ft_strjoin(ex->path, exec->args[0]);
		if (!ex->exec_path)
			ft_exit_fail("exec path problem");
		// else
		// 	printf("->%s<-\n", ex->exec_path);
		if (access(ex->exec_path, X_OK) == 0)
		{
			// printf("access->%s<-\n", ex->exec_path);
			(1) && (free(ex->path), flag_access = 1);
			break;
		}
		else
		{
			free(ex->path);
			free(ex->exec_path);
			(1) && (ex->i++, flag_access = 0);
		}
	}
	if (flag_access == 0)
	{
		ex->current_dir = (char *)malloc(PATH_MAX);
		getcwd(ex->current_dir, PATH_MAX);
		ex->path_in = ft_strchr(exec->args[0], '/');
		ex->exec_path = ft_strjoin(ex->current_dir, ex->path_in);
		if (access(ex->exec_path, X_OK) == 0)
			if(ft_strncmp(ex->current_dir, ex->exec_path, (ft_strlen( ex->exec_path))))
				flag_access = 1;
		free(ex->current_dir);
	}
	if(flag_access == 1)
		exec->exec_path = ex->exec_path;
	else
		if (access(exec->args[0], X_OK) == 0)
			(exec->exec_path = exec->args[0], flag_access = 1);
	free(ex->path_split);
	free(ex);
	if (flag_access == 0)
	{
		not_found(exec->args[0]);
		// ft_putstr_fd("\033[0;31mminishell: \033[0m", 2);
		// ft_putstr_fd("\033[0;31m command not found\033[0m: ", 2);
		// ft_putstr_fd(exec->args[0], 2);
		// ft_putstr_fd("\n", 2);
		// exit(127);
	}
}



void one_cmd(t_command **commands, int pid,  t_env **envex , char ** env)
{
	int status = 0;
	if (command_check(commands, envex) == 0)
		return;
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		if (pid == 0)
		{
			search_exec_2(commands, env);
			if (execve((*commands)->exec_path, (*commands)->args, env)== -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	exit_status(status >> 8);
	catch = 1;
	return;
}



void execution_cmd(t_command **commands, char **env, t_env **envex, int fd) 
{
    int fd2[2], status, f, pid;

	f = 0;
	int j = dup(1);
	int n = dup(0);
    while (*commands != NULL) 
	{

		fill_ter((*commands)->args, envex, 0);

		if ((*commands)->rdrect[f] != NULL) 
		{
			fd = redire(commands);
<<<<<<< HEAD
			if (fd < 0)
			{
				dup2(j, 1);
				dup2(n, 0);
				close(j);
				close(n);
				return ;
			}

=======
			// if (fd < 0) 
			// 	exit(EXIT_FAILURE);
>>>>>>> b7f202203f5028a4ee0fa7d7f7650c343e1de6ba
			close(fd);
		}
		if ((*commands)->redir_out != 1 && (*commands)->dredir_out != 1)
			dup2(j, 1);
	    pipe(fd2);
        pid = fork();
        if (pid == -1)
		{
            perror("fork");
            return;
        }
        if (pid == 0) 
		{
			close(fd2[0]);
			if ((*commands)->next && (*commands)->redir_out != 1 && (*commands)->dredir_out != 1)
				dup2(fd2[1], 1);
			close(fd2[1]);
		
            if ((*commands)->args[0] != NULL && command_check(commands, envex) == 1) 
			{
                search_exec_2(commands, env);
                if (execve((*commands)->exec_path, (*commands)->args, env) == -1) 
				{
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            exit(0);
        } 
		else 
		{
            close(fd2[1]);
			if ( (*commands)->next)
				dup2(fd2[0], 0);
			close(fd2[0]);
			fill_ter((*commands)->args, envex, 1);
			
        }
        *commands = (*commands)->next;
    }
	dup2(j, 1);
	dup2(n, 0);
	close(j);
	close(n);
	while (wait(&status) != -1);
	exit_status(status >> 8);
	catch = 1;
}


void fill_ter(char **str, t_env **envex, int l)
{
	t_env *ev;
	ev = *envex;
	int i = 0;
	while(str[i])
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
			if(str[i] && l == 0)	
				ev->value = ft_strdup(str[i]);
			else	
				ev->value = ft_strdup("");
		}
		ev = ev->next;
	}
}

char **refiller(char **env, t_env **envex)
{
	t_env *enve;
	char *tmp;
	char *tmp2;
	char **new_env;
	enve = *envex;
	int i =0;
	
	while(enve)
	{
		if (enve->q == 1 && enve->vari != NULL && enve->value != NULL)
			i++;
		enve = enve->next;
	}
	
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	enve = *envex;
	while(enve)
	{
		if (enve->q == 1 && enve->vari != NULL && enve->value != NULL)
		{
			tmp2 = ft_strjoin(enve->vari, "=");
			tmp = ft_strjoin(tmp2, enve->value);
			free(tmp2);
			new_env[i] = ft_strdup(tmp);
			free(tmp);
			i++;
		}
			enve = enve->next;
	}
	new_env[i] = NULL;
	i =0;
	// while (env[i])
	// {
	// 	free(env[i]);
	// 	env[i] = NULL;
	// 	i++;
	// }
	env = NULL;
	env = new_env;
	return(env);
	
}

char	**exec_check(t_command **command, char **env, int enp)
{
	static t_env *envex;
	
	ft_filler(&envex, env);
	(envex->empty = enp, (*command)->ex = enp);
	(*command)->evr = env;
	int fd = 0;
<<<<<<< HEAD
=======
	printf ("empty = %d\n", envex->empty);
>>>>>>> b7f202203f5028a4ee0fa7d7f7650c343e1de6ba
	if ((*command)->next ==NULL)
	{
		
		fill_ter((*command)->args, &envex, 0);
		if ((*command)->rdrect)
				fd = redire(command);
		if (fd < 0 )
			return (refiller(env,  &envex));
		one_cmd(command, 0, &envex, env);
		close(fd);
		return (refiller(env,  &envex));
	}
	execution_cmd(command, env, &envex, fd);
	
	return (refiller(env,  &envex));
}
