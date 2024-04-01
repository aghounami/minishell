/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:12:26 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/30 02:36:03 by aghounam         ###   ########.fr       */
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
			printf("minishell: exit: %s: numeric argument required\n", \
				my_exit->args[1]);
			exit(255);
		}
		else
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
	}
}

void	ft_exit_mini(t_command **command)
{
	t_command	*my_exit;
	int			i;

	(1) && (i = 0, my_exit = *command);
	i++;
	i--;
	printf("exit\n");
	if (my_exit->args[1] != NULL && my_exit->args[2] != NULL)
		case_too_many_args(my_exit);
	else if (my_exit->args[1] != NULL)
	{
		if (check_numeric(my_exit->args[1]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", \
				my_exit->args[1]);
			exit(255);
		}
		else
			exit(ft_atoi(my_exit->args[1]));
	}
	else
		exit(0);
}
