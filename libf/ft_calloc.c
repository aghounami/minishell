/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:32:27 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/02 13:45:50 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}
/*#include <stdio.h>
#include <stdlib.h>

int main() {
size_t count = 4;
size_t size = 2;

int *allocated_array = (int *)ft_calloc(count, size);

if (allocated_array) {
printf("Memory allocated and initialized with zeros:\n");
for (size_t i = 0; i < count; i++) {
printf("%d ", allocated_array[i]);
}
printf("\n");

free(allocated_array);
} else {
printf("Memory allocation failed!\n");
}
return 0;
}*/