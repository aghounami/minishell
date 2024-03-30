/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:29:18 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/09 12:37:03 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_world(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	ft_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	f_free(char **n, int le)
{
	int	i;

	i = 0;
	while (i < le)
	{
		free(n[i]);
		n[i] = NULL;
		i++;
	}
	free(n);
	n = NULL;
}

static char	**ft_cpy(char **str, char const *s, char c)
{
	int				j;
	size_t			len;
	unsigned int	i;

	j = 0;
	i = 0;
	while (j < count_world(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = ft_len(s + i, c);
		str[j] = ft_substr(s, i, len);
		if (str[j] == NULL)
		{
			f_free(str, j);
			return (NULL);
		}
		while (s[i] && s[i] != c)
			i++;
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (s == NULL)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (count_world(s, c) + 1));
	if (res == NULL)
		return (NULL);
	res = ft_cpy(res, s, c);
	if (!res)
		return (NULL);
	return (res);
}
/*#include <stdio.h>
  int main()
  {
  char *input = "*sw*er******";
  char delimiter = '*';
  char **ret = ft_split(input, delimiter);
  int i = 0;
  while (ret[i] != NULL)
  {
  printf("%s\n", ret[i]);
  free(ret[i]);
  i++;
  }
  free(ret);
  return 0;
  }*/