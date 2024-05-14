/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/14 10:34:32 by hel-magh         ###   ########.fr       */
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
void search_exec_2(t_command **command, char **env)
{
	t_command *exec;
	t_exec *p_exec;
	int flag_access;
	
	(1) && (flag_access = 0, exec = *command, p_exec = malloc(sizeof(t_exec)));
	if (!p_exec)
		ft_exit_fail("malloc failed");
	p_exec->path_split = ft_split(get_env("PATH", env), ':');
	if (!p_exec->path_split)
		ft_exit_fail("split failed");
	p_exec->i = 0;
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
			(1) && (free(p_exec->path), flag_access = 1);
			break;
		}
		else
		{
			free(p_exec->path);
			free(p_exec->exec_path);
			(1) && (p_exec->i++, flag_access = 0);
		}
	}
	if (flag_access == 0)
	{
		p_exec->current_dir = (char *)malloc(PATH_MAX);
		getcwd(p_exec->current_dir, PATH_MAX);
		p_exec->path_in = ft_strchr(exec->args[0], '/');
		p_exec->exec_path = ft_strjoin(p_exec->current_dir, p_exec->path_in);
		if (access(p_exec->exec_path, X_OK) == 0)
			if(ft_strncmp(p_exec->current_dir, p_exec->exec_path, (ft_strlen( p_exec->exec_path))))
				flag_access = 1;
	free(p_exec->current_dir);
	}
	if(flag_access == 0)
		if (access(exec->args[0], X_OK) == 0)
			flag_access = 1;
	exec->exec_path = p_exec->exec_path;
	free(p_exec->path_split);
	free(p_exec);
	if (flag_access == 0)
	{
		ft_putstr_fd("\033[0;31mminishell: \033[0m", 2);
		ft_putstr_fd("\033[0;31m command not found\033[0m: ", 2);
		ft_putstr_fd(exec->args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}


// int	command_check_2(t_command **command, t_env **envex)
// {
// 	t_command	*exec;
	
// 	exec = *command;
// 	if (!exec->args[0])
// 		return(0);
// 	else if (!ft_strncmp("cd", exec->args[0], 3))
// 		return (cd_checker(command), 0);
// 	else if (!ft_strncmp("echo", exec->args[0], 5)
// 		|| !ft_strncmp("ECHO", exec->args[0], 5))
// 		return (ft_echo(command), 0);
// 	else if (!ft_strncmp("export", exec->args[0], 7))
// 		return (ft_export(command, envex), 0);
// 	else if (!ft_strncmp("pwd", exec->args[0], 4)
// 		|| !ft_strncmp("PWD", exec->args[0], 4))
// 		return (ft_pwd(), 0);
// 	else if (!ft_strncmp("unset", exec->args[0], 6))
// 		return (ft_unset(command,envex), 0);
// 	else if (!ft_strncmp("env", exec->args[0], 4)
// 		|| !ft_strncmp("ENV", exec->args[0], 4))
// 		return (ft_env(envex), 0);
// 	else if (!ft_strncmp("exit", exec->args[0], 5))
// 		return (ft_exit_mini(command), 0);
// 	return (1);
// }
void one_cmd(t_command **commands, int pid,  t_env **envex , char ** env)
{
	
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
		{
			
			waitpid(pid, 0, 0);
		}
	}
	return;
}

// int checker_in(t_command **command)
// {
// 	t_command *cmd = *command;
//     int i = 0;

    
//     while (cmd->redirection[i])
//      {
//          if (ft_strncmp(cmd->redirection[i], "<", 2) == 0)
// 		 	return(1);
// 		i++;
//     }
// 	return(0);
// }

void execution_cmd(t_command **commands, char **env, t_env **envex, int fd) {
    int prev_pipe[2], next_pipe[2], status, pid, n, j;

    prev_pipe[0] = -1;
    prev_pipe[1] = -1;

    while (*commands != NULL) 
	{
        
        (n = dup(STDIN_FILENO), j = dup(STDOUT_FILENO));

        
        if ((*commands)->next != NULL && pipe(next_pipe) == -1) 
		{
            perror("pipe");
            return;
        }

        pid = fork();
        if (pid == -1)
		{
            perror("fork");
            return;
        }

        if (pid == 0) 
		{ 
            if (prev_pipe[0] != -1) 
                (dup2(prev_pipe[0], STDIN_FILENO), close(prev_pipe[0]), close(prev_pipe[1]));

            
            if ((*commands)->next != NULL) 
                (dup2(next_pipe[1], STDOUT_FILENO), close(next_pipe[0]), close(next_pipe[1]));

            if ((*commands)->redirection) 
			{
                fd = redire(commands);
                if (fd < 0) 
                    exit(EXIT_FAILURE);
            }
            if ((*commands)->args[0] != NULL && strncmp("exit", (*commands)->args[0], 4) != 0 && command_check(commands, envex) == 1) 
			{
                search_exec_2(commands, env);
                if (execve((*commands)->exec_path, (*commands)->args, env) == -1) 
				{
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } 
			else 
                exit(0);
            
        } 
		else 
		{ 
            if (prev_pipe[0] != -1) 
                (close(prev_pipe[0]), close(prev_pipe[1]));
            (prev_pipe[0] = next_pipe[0], prev_pipe[1] = next_pipe[1]);
            (dup2(n, STDIN_FILENO), dup2(j, STDOUT_FILENO),  close(n), close(j));

            *commands = (*commands)->next;
        }
    }
    (close(prev_pipe[0]), close(prev_pipe[1]));

    while (wait(&status) > 0);
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

char	**exec_check(t_command **command, char **env)
{
	static t_env *envex;
	ft_filler(&envex, env);
	(*command)->evr = env;
	int fd = 0;

	if ((*command)->next ==NULL)
	{
		// if ((*command)->redir_in)
		// 		fd[0] = redire_in(command);
		
		if ((*command)->redirection)
				fd = redire(command);
		if (fd < 0 )
			return (refiller(env,  &envex));
		one_cmd(command, 0, &envex, env);
		close(fd);
		return (refiller(env,  &envex));
	}
	execution_cmd(command, env, &envex, fd);
	return (refiller(env,  &envex));
	close(fd);
}
