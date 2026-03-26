/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:34:58 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:32:18 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_one(t_env **lst, char *raw)
{
	t_env	*node;
	char	*eq;
	char	*name;

	eq = ft_strchr(raw, '=');
	if (!eq)
		return (0);
	name = ft_substr(raw, 0, eq - raw);
	if (!name)
		return (-1);
	node = env_new_node(name, eq + 1);
	free(name);
	if (!node)
		return (-1);
	env_add_back(lst, node);
	return (0);
}

t_env	*env_init_from_envp(char **envp)
{
	t_env	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (envp[i])
	{
		if (add_one(&lst, envp[i]) < 0)
		{
			env_free_list(lst);
			return (NULL);
		}
		i++;
	}
	return (lst);
}

static int	count_valued(t_env *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		if (lst->value)
			n++;
		lst = lst->next;
	}
	return (n);
}

static char	*make_entry(t_env *node)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(node->name, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, node->value);
	free(tmp);
	return (entry);
}

char	**env_to_array(t_env *lst)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (count_valued(lst) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->value)
		{
			arr[i] = make_entry(lst);
			if (!arr[i])
			{
				while (i > 0)
					free(arr[--i]);
				return (free(arr), NULL);
			}
			i++;
		}
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}
