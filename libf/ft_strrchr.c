/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:12:24 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/01 23:05:13 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*str;

	str = (char *)s;
	i = ft_strlen(s);
	while (str[i] != (char)c && i > 0)
		i--;
	if (str[i] == (char)c)
	{
		return (str + i);
	}
	return (NULL);
}
