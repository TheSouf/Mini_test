/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 18:31:26 by elibrahi          #+#    #+#             */
/*   Updated: 2025-04-20 18:31:26 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*# include <stdio.h>
# include <string.h>

int	main(void)
{
	char	s1[] = "abc";
	char    s2[] = "arc";

	printf("Man %d\n", strncmp(s1, s2, 6));
	printf("Moi %d\n", ft_strncmp(s1, s2, 6));
}*/