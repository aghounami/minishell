#include "minishell.h"


char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = strlen(s1);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*sub;

	if (!s)
		return (NULL); 
	str = (char *)s;
	if (start >= strlen(s))
		return (ft_strdup(""));
	if (len > (strlen(s) - start))
		len = strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}


static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
			{
				s++;
			}
		}
		else
		{
			s++;
		}
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
	while (j <= count_words(s, c))
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
	res = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (res == NULL)
		return (NULL);
	res = ft_cpy(res, s, c);
	if (!res)
		return (NULL);
	return (res);
}
