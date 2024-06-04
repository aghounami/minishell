/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:12:26 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/04 14:54:21 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			if (str[0] != '+' && str[0] != '-')
				return (0);
		i++;
	}
	return (1);
}

void	case_too_many_args(t_command *my_exit)
{
	{
		if (check_numeric(my_exit->args[1]) == 0)
		{
			ft_putstr_fd("minishell: exit:", 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			exit(255);
		}
		else
		{
			ft_putstr_fd("minishell: exit:", 2);
			ft_putstr_fd("too many arguments\n", 2);
			return ;
		}
	}
}

void	ft_exit_mini(t_command **command)
{
	t_command	*my_exit;
	int			i;

	(1) && (i = 0, my_exit = *command);
	if (my_exit->ex == 0)
		printf("exit\n");
	if (my_exit->args[1] != NULL && my_exit->args[2] != NULL)
		case_too_many_args(my_exit);
	else if (my_exit->args[1] != NULL)
	{
		if (check_numeric(my_exit->args[1]) == 0)
		{
			ft_putstr_fd("minishell: exit:", 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			exit(255);
		}
		else
			exit(ft_atoi(my_exit->args[1]));
	}
	else
		exit(0);
}
