/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 18:57:34 by elibrahi          #+#    #+#             */
/*   Updated: 2025-04-20 18:57:34 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	value;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ptr[i] = value;
		i++;
	}
	return (b);
}
/*#include <stdlib.h>
#include <stdio.h>

void	main()
{
	void	*str;
	str = malloc(sizeof(char)* 6);

	ft_memset(str, 65, 2);
	printf("test %s", (char *)str);
}*/
