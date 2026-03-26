/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:53:43 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:28:52 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_one(t_shell *shell, char *name)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = shell->env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env_list = current->next;
			free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (args[i])
	{
		unset_one(shell, args[i]);
		i++;
	}
	return (ret);
}
