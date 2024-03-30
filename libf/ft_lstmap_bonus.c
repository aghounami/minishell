/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:53:21 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/12 12:29:25 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*first;

	first = NULL;
	while (lst)
	{
		new = ft_lstnew(NULL);
		if (!new)
		{
			ft_lstclear(&first, del);
			{
				return (NULL);
			}
		}
		new->content = f(lst->content);
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
// void *ff(void *s)
// {
// 	return ("mehdi");
// }
// void ft_free(void *ds)
// {
// 	free(ds);
// }
// #include <stdio.h>

// int main()
// {
// 	char *str = "ahmed";
// 	t_list *new = ft_lstnew(str);
// 	new->content = malloc(10);
// 	ft_strlcpy(new->content, str, sizeof(str));
// 	printf("nom: %s\n", new->content);
// 	t_list *s2 = ft_lstnew(str);
// 	s2->content = malloc(10);
// 	ft_strlcpy(s2->content, str, sizeof(str));
// 	printf("name : %s\n", s2->content);
// 	new->next = s2;
// 	t_list *res = ft_lstmap(new, ff, ft_free);
// 	// printf("nom: %s\n", new->content);
// 	// printf("name : %s\n", s2->content);
// 	while (res)
// 	{
// 		printf("%s\n", res->content);
// 		res = res->next;
// 	}
// }
