/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:35:42 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 14:42:53 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst)
		{
			if (!lst->next)
				return (lst);
			lst = lst->next;
		}
	}
	return (lst);
}
// #include <stdio.h>

//   int main()
//   {
//   char *str = "sgdgd";
//   char *fg = "ahmed";
//   t_list *h = ft_lstnew(str);
//   t_list *s =ft_lstnew(str);
//   t_list *t = ft_lstnew(fg);

//   h->next = s;
//   s->next = t;
//   t->next = NULL;
//   t_list *nnn  = ft_lstlast(h);
//   printf("%s", nnn->content);
//   free(h);
//   free(s);
//   free(t);
//   return 0;
//   }