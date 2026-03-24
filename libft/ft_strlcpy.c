/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 18:58:30 by elibrahi          #+#    #+#             */
/*   Updated: 2025-04-20 18:58:30 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (!dest || size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/*
#include <stdio.h>
#include <string.h>

void	main()
{
	char src[] = "dest copie";
	char dest[20];
	
	unsigned int size_copied = ft_strlcpy(dest, src, sizeof(dest));
	
	printf("Destination après copie : %s\n", dest);
	printf("Longueur de la chaîne source : %u\n", size_copied);
}*/
