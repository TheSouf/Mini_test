/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elibrahi <elibrahi@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 18:56:33 by elibrahi          #+#    #+#             */
/*   Updated: 2025-04-20 18:56:33 by elibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (sign == -1 && result > 2147483648)
			return (-1);
		if (sign == 1 && result > 2147483647)
			return (-1);
	}
	return (sign * (int)result);
}
/*#include <stdio.h>
#include <stdlib.h>

void	main()
{
	printf("My Atoi, %d\n", ft_atoi("2147483648"));
	printf("Man Atoi, %d", atoi("2147483648"));
	//return (0);
}*/
