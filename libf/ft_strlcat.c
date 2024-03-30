/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:26:19 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/07 13:01:45 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	if ((dst == NULL && src == NULL) && size == 0)
		return (0);
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = 0;
	if (size <= dstlen)
	{
		return (srclen + size);
	}
	while (src[i] && dstlen + i + 1 < (size))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen + i < size)
	{
		dst[dstlen + i] = '\0';
	}
	return (dstlen + srclen);
}
/*#include <stdio.h>
  int main() 
  {
  char dest[] = "Hello ";
  const char *source = "World";
  int result = ft_strlcat(dest, source, 5);

  printf("Concatted stringena: %s\n", dest);
  printf("Result: %d\n", result);

  return 0;
  }*/