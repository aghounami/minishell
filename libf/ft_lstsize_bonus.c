/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:57:51 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 13:01:21 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
// #include <stdio.h>
//   int main()
//   {
//   char *content = "hello world";
//   t_list *new = ft_lstnew(content);
//   t_list *first = ft_lstnew(content);

//   new->next = first;
//   int size = ft_lstsize(new);
//   printf("%d", size);

// //   if (new != NULL)
// //   {
// //   printf("New content : %s\n", (char *)new->content);
// //   printf("next : %s\n",(void *)new->next);
// //   free (new->content);
// //   free (new->next);
// //   free(new);
// //   }
// //   else
// //   {
// //   printf("failed");
// //   }

// //   return 0;
//   }
