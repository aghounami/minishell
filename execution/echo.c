/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 05:32:39 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/04 13:07:47 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	er_print(char *str, char *str2, int i)
{
	exit_status(i);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
}

int	check_n(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_command **command)
{
	int	i;
	int	n;	

	i = 1;
	n = 0;
	if ((*command)->args[1] && (*command)->args[1] \
			&& ft_strncmp((*command)->args[1], "-n", 2) == 0 \
			&& check_n((*command)->args[1]) == 1)
	{
		n = 1;
		i++;
		while ((*command)->args[i]
			&& (ft_strncmp((*command)->args[i], "-n", 2) == 0 \
			&& check_n((*command)->args[i]) == 1))
			i++;
	}
	while ((*command)->args[i])
	{
		ft_putstr_fd((*command)->args[i], 1);
		if ((*command)->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}
