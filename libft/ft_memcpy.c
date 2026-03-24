/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:02:07 by elibrahi          #+#    #+#             */
/*   Updated: 2025/04/18 17:37:01 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	tmp_dest = (unsigned char *) dest;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(tmp_dest++) = *(tmp_src++);
		n--;
	}
	return (dest);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	char src[] = "Bonjour, tout le monde!";
	char dest[50];

	printf("Ma Fonction ft_memcpy: %p\n", ft_memcpy(dest, src, 5));
	printf("Man Memcpy: %p\n", memcpy(dest, src, 5));
	return (0);
}*/
