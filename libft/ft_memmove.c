/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 18:57:26 by elibrahi          #+#    #+#             */
/*   Updated: 2025-04-20 18:57:26 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s || size == 0)
		return (dest);
	if (d > s)
	{
		while (size--)
			d[size] = s[size];
	}
	else
	{
		while (size--)
			*d++ = *s++;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

void	main()
{
	char texte[] = "Bonjour";

	printf("Résultat : %p", ft_memmove(texte + 2,texte, 5));
}*/
