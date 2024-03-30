/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:34:31 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 15:02:51 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}
// #include <stdio.h>

// int main()
// {
// 	t_list	*lst = NULL;	
// 	t_list 	*new = ft_lstnew("hello");
// 	t_list *new2 = ft_lstnew("world");
// 	ft_lstadd_back(&lst, new);
// 	ft_lstadd_back(&lst, new2);
//     while (lst)
//     {
//         printf("%s ", (char *)lst->content);
//         lst = lst->next;
//     }
// 	return 0;
// }
