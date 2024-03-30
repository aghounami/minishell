/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:52:50 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/12 12:30:19 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst && lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
// void ft_free(void *content)
// {
// 	content = NULL;
// }
// void print_list(t_list *lst) {
//     while (lst) {
//         printf("%s -> ", (char *)lst->content);
//         lst = lst->next;
//     }
//     printf("NULL\n");
// }
// #include <stdio.h>
// int main()
// {
// 	t_list **list = (t_list **)malloc(sizeof(t_list));
// 	t_list *new = ft_lstnew("hello");
// 	t_list *first = ft_lstnew("world");	
// 	ft_lstadd_back(list, new);
// 	ft_lstadd_back(list, first);
// 	printf("%p\n", (void *)new);
// 	printf("%p\n", (void *)first);
// 	print_list(*list);
// 	ft_lstclear(list, ft_free);
// 	print_list(*list);
// 	printf("%p\n", (void *)new);
// 	printf("%p\n", (void *)first);
// 	return 0;
// }
