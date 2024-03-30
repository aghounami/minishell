/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:12:26 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/30 01:09:29 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_mini(t_command **command)
{
	t_command	*my_exit;
	int			i;

	i = 0;
	my_exit = *command;
	printf("exit\n");
	if (my_exit->args[1])
		i = ft_atoi(my_exit->args[1]);
	exit(i);
}
