/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:52:52 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:29:57 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_home(t_shell *shell)
{
	t_env	*node;

	node = env_find(shell->env_list, "HOME");
	if (!node || !node->value)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	return (node->value);
}

static char	*get_oldpwd(t_shell *shell)
{
	t_env	*node;

	node = env_find(shell->env_list, "OLDPWD");
	if (!node || !node->value)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}
	ft_putendl_fd(node->value, 1);
	return (node->value);
}

static char	*get_target(char **args, t_shell *shell)
{
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (get_home(shell));
	if (ft_strcmp(args[1], "-") == 0)
		return (get_oldpwd(shell));
	return (args[1]);
}

static int	do_chdir(char *target, char *old_pwd)
{
	if (chdir(target) != -1)
		return (0);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(old_pwd);
	return (1);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*target;

	if (args[1] && args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	target = get_target(args, shell);
	if (!target)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (do_chdir(target, old_pwd))
		return (1);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		update_env_var(shell, "PWD", new_pwd);
	update_env_var(shell, "OLDPWD", old_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
