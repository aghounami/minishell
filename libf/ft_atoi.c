/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:12 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/11 19:09:21 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	final(unsigned long int nbr, int po)
{
	long	num;

	if (nbr > 9223372036854775807)
	{
		if (po == 1)
			return (-1);
		else
			return (0);
	}
	num = nbr * po;
	return (num);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (final(result, sign));
}

// #include <stdio.h>
// int main()
// {
// 	char str[] = "-92233720368547758054577";
// 	printf("%d\n", atoi(str));
// 	printf("%d\n", ft_atoi(str));
// }
