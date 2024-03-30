/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:54:32 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 13:07:15 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res [i] = '\0';
	return (res);
}
// char ft_f(unsigned int n, char c)
//   {
//   return (c + 32);
//   }
// #include <stdio.h>
// int main()
// {
// char str[] = "HELLO";
// char *ar =  ft_strmapi(str,  &ft_f);
// printf("%s", ar);
// }
