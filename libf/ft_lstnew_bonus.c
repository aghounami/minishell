/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:25:44 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/04 15:21:14 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*#include <stdio.h>
  int main()
  {
  char *content = "hello world";
  t_list *new = ft_lstnew(content);

  if (new != NULL)
  {
  printf("New content : %s\n", (char *)new->content);
  printf("next : %s\n",(void *)new->next);
  free (new->content);
  free (new->next);
  free(new);
  }
  else
  {
  printf("failed");
  }

  return 0;
  }*/
