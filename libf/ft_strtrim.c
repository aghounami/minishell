/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:01:53 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/07 12:20:56 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chek(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		total;
	char	*res;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && chek(set, s1[start]))
		start++;
	while (end > start && chek(set, s1[end]))
		end--;
	total = end - start + 1;
	res = ft_substr(s1, start, total);
	return (res);
}
/*#include <stdio.h>
  int main()
  {
  char str[] = "ar   hello, world   ar";
  char *set = "ar";
  printf("%s\n", ft_strtrim(str, set));
  }*/