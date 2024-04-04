/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:50:52 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/08 20:18:19 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	total;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	total = lens1 + lens2 + 1;
	res = (char *)malloc(total);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, total);
	ft_strlcpy(res + lens1, s2, total);
	return (res);
}
/*#include <stdio.h>
  int main()
  {
  char str[] = "hello ";
  char dst[] = "world!";
  printf("%s", ft_strjoin(str, dst));
  }*/