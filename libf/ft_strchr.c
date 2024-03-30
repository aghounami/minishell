/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:57:22 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/03 23:08:51 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if ((char)c == str[i])
		{
			return (str + i);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return (str + i);
	}
	return (NULL);
}
