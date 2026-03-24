/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:54:10 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/22 20:32:22 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
static int	is_numeric(char *str)
{
	int	i;
 
	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
 
static void	exit_non_numeric(char **args, t_shell *shell)
{
	write(2, "exit: ", 6);
	write(2, args[1], ft_strlen(args[1]));
	write(2, ": numeric argument required\n", 28);
	env_free_list(shell->env_list);
	exit(2);
}
 
int	builtin_exit(char **args, t_shell *shell)
{
	long	code;
 
	if (!args[1])
	{
		code = shell->last_exit_code;
		env_free_list(shell->env_list);
		exit((int)code);
	}
	if (!is_numeric(args[1]))
		exit_non_numeric(args, shell);
	if (args[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	code = ft_atoi(args[1]);
	env_free_list(shell->env_list);
	exit((int)(code & 255));
}
