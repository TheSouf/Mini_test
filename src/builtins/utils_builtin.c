/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:14:49 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/20 18:12:34 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_var(t_shell *shell, char *name, char *value)
{
	t_env	*node;
	char	*new_val;
 
	node = env_find(shell->env_list, name);
	if (node)
	{
		new_val = ft_strdup(value);
		if (!new_val)
			return ;
		free(node->value);
		node->value = new_val;
	}
	else
	{
		node = env_new_node(name, value);
		if (node)
			env_add_back(&shell->env_list, node);
	}
}

void	init_shlvl(t_shell *shell)
{
	t_env	*node;
	int		lvl;
	char	*new_lvl;
 
	node = env_find(shell->env_list, "SHLVL");
	if (node && node->value)
		lvl = ft_atoi(node->value) + 1;
	else
		lvl = 1;
	if (lvl < 0)
		lvl = 0;
	new_lvl = ft_itoa(lvl);
	if (!new_lvl)
		return ;
	update_env_var(shell, "SHLVL", new_lvl);
	free(new_lvl);
}
