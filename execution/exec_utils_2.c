/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:14:30 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 16:25:57 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_envx(char *str, t_env **env)
{
	t_exec		ev;
	t_env		*inv;

	inv = *env;
	if (*env == NULL)
		return (NULL);
	ft_memset(&ev, 0, sizeof(inv));
	while (inv)
	{
		if (strncmp(str, inv->vari, ft_strlen(inv->vari)) == 0)
		{
			ev.tmp = ft_strdup(inv->value);
			if (!ev.tmp)
				ft_exit_fail("env list");
			return (ev.tmp);
		}
		inv = inv->next;
	}
	return (NULL);
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

void	pwd_update(t_env **env, char *str)
{
	t_env	*envex;
	char	*tmp2 ;

	envex = *env;
	tmp2 = (char *)malloc(PATH_MAX);
	if (!tmp2)
	{
		perror("PWD");
		exit(1);
	}
	while (envex)
	{
		if (ft_strncmp(envex->vari, str, ft_strlen(envex->vari)) == 0)
		{
			getcwd(tmp2, PATH_MAX);
			(free(envex->value), envex->value = NULL);
			envex->value = ft_strdup(tmp2);
			(free(tmp2), tmp2 = NULL);
		}
		envex = envex->next;
	}
}

int	ft_lstsize_ex(t_command *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
