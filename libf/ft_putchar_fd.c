/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:40:58 by aghounam          #+#    #+#             */
/*   Updated: 2023/11/12 12:29:49 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
// #include <fcntl.h>
// int main()
// {
//   int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   ft_putchar_fd('H', fd);
//   ft_putchar_fd('e', fd);
//   ft_putchar_fd(-1, fd);
//   ft_putchar_fd('l', fd);
//   ft_putchar_fd('l', fd);
//   ft_putchar_fd('o', fd);
// }
