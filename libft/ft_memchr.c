/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:16:08 by elibrahi          #+#    #+#             */
/*   Updated: 2025/04/18 17:57:31 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	uc;

	str = (unsigned char *)s;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == uc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char data[] = "Hello world";
	char *result = ft_memchr(data, 'a', 11);
	//char *result = memchr(data, 'a', 11);
	
	if (result)
		printf("Trouvé : %c\n", *result);
	else
		printf("Pas trouvé\n");
	return (0);
}*/
