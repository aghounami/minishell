/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:30:28 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 12:40:33 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
// #include <stdio.h>

// int main()
// {
// 	t_list *list;

// 	t_list *new = ft_lstnew("ahmed");
// 	ft_lstadd_front(&list, new);
// 	printf("%s", list->content);
// }