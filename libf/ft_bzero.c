/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:45:08 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/04 21:53:49 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*#include <stdio.h>
int main()
  {
  char data[] = "hello";
  ft_bzero(data, sizeof(data));
  for (int i = 0; i < 5; i++)
  printf("%d", data[i]);
  return 0;
  }*/