/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:16:11 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:32:56 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*alloc_node(char *name)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = NULL;
	new->next = NULL;
	return (new);
}

t_env	*env_new_node(char *name, char *value)
{
	t_env	*new;

	new = alloc_node(name);
	if (!new)
		return (NULL);
	if (!value)
		return (new);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*cur;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_env	*env_find(t_env *lst, char *name)
{
	if (!lst || !name)
		return (NULL);
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	env_free_list(t_env *lst)
{
	t_env	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->name);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = next;
	}
}
