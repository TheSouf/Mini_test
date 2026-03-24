/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 18:58:05 by elibrahi          #+#    #+#             */
/*   Updated: 2025-04-20 18:58:05 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	j;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	i = len_dest;
	j = 0;
	if (size == 0 || size <= len_dest)
		return (size + len_src);
	while (src[j] != '\0' && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (len_dest + len_src);
}
/*
# include <stdio.h>
# include <string.h>

int	main(void)
{
	char dest[20] = "Hello, ";
    	char src[] = "World!";

	printf("%u\n", ft_strlcat(dest, src, 9));
	//printf("%u\n", strlcat(dest, src, 9));
	printf("%s", dest);
}*/
