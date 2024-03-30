/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:00:35 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/10 13:08:12 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (i < len && s1[i])
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s2[j] && s1[i + j] == s2[j] && (i + j) < len)
			{
				j++;
			}
			if (s2[j] == '\0')
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
// #include "libft.h"
// #include <stdio.h>

// int main()
// {
// 	const char *haystack = "";
// 	const char *needle = "q";
// 	size_t len = ft_strlen(haystack);

// 	char *result = ft_strnstr(haystack, needle, len);

// 	if (result != NULL)
// 	{
// 		printf("%s\n", result);
// 	}
// }
