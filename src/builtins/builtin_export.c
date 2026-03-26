/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:53:20 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:27:16 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_list(t_shell *shell)
{
	t_env	*cur;

	cur = shell->env_list;
	while (cur)
	{
		write(1, "declare -x ", 11);
		write(1, cur->name, ft_strlen(cur->name));
		if (cur->value)
		{
			write(1, "=\"", 2);
			write(1, cur->value, ft_strlen(cur->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		cur = cur->next;
	}
}

static void	set_or_update(t_shell *shell, char *name, char *value)
{
	t_env	*node;
	char	*new_val;

	node = env_find(shell->env_list, name);
	if (node)
	{
		if (value)
		{
			new_val = ft_strdup(value);
			if (!new_val)
				return ;
			free(node->value);
			node->value = new_val;
		}
	}
	else
	{
		node = env_new_node(name, value);
		if (node)
			env_add_back(&shell->env_list, node);
	}
}

static int	export_one(char *arg, t_shell *shell)
{
	char	*eq;
	char	*name;

	eq = ft_strchr(arg, '=');
	if (eq)
		name = ft_substr(arg, 0, eq - arg);
	else
		name = ft_strdup(arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		write(2, "export: `", 9);
		write(2, name, ft_strlen(name));
		write(2, "': not a valid identifier\n", 26);
		free(name);
		return (1);
	}
	if (eq)
		set_or_update(shell, name, eq + 1);
	else
		set_or_update(shell, name, NULL);
	free(name);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_export_list(shell);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (export_one(args[i], shell) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
