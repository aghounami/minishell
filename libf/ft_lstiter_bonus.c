/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:40:25 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 13:59:33 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f || !lst)
	{
		return ;
	}
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
// void modifier(void *content)
// {
// 	char *s = (char *)content;
// 	while (*s)
// 	{
// 		if (*s >= 'a' && *s <= 'z')
// 		{
// 			*s -= 32;
// 		}
// 		s++;
// 	}
// }
// #include <stdio.h>
// int main()
// {
// 	t_list *new = ft_lstnew("salut");
// 	new->content = malloc(10);
// 	ft_strlcpy(new->content, "salut", 10);
// 	t_list *first = ft_lstnew("hello");
// 	first->content = malloc(10);
// 	ft_strlcpy(first->content, "hello", 10);
// 	new->next = first;
// 	ft_lstiter(new, modifier);
// 	printf("%s\n", new->content);
// 	printf("%s\n", first->content);
// }
