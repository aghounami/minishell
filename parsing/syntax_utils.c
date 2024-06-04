/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:48:49 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/04 12:29:34 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_pipe_line_first(t_elem **elem)
{
	t_elem	*tmp;

	tmp = *elem;
	while (tmp && tmp->token == WHITE_SPACE)
		tmp = tmp->next;
	if (tmp && tmp->token == PIPE_LINE)
		return (1);
	return (0);
}

void	malloc_fail(void)
{
	ft_putstr_fd("malloc failed\n", 2);
	exit(1);
}

int	exit_status(int status)
{
	static int	e_status = 0;

	if (status != -1 && g_catch == 0)
		e_status = status;
	return (e_status);
}

void	empty_line(t_varr **var)
{
	printf("exit\n");
	free((*var)->line);
	free((*var)->envp);
	free((*var));
	exit(0);
}

void	free_all(t_elem **list, t_command **command, t_varr **var)
{
	add_history((*var)->line);
	free((*var)->line);
	ft_free_lexer(list);
	ft_free_command(command);
}
