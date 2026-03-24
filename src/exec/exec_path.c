/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:27:50 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/18 21:42:08 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
static char	*get_the_path(t_shell *shell)
{
	t_env	*node;
 
	node = env_find(shell->env_list, "PATH");
	if (!node || !node->value)
		return (NULL);
	return (node->value);
}
 
static char	*build_the_path(char *dir, char *cmd)
{
	char	*half_path;
	char	*full_path;
 
	half_path = ft_strjoin(dir, "/");
	if (!half_path)
		return (NULL);
	full_path = ft_strjoin(half_path, cmd);
	free(half_path);
	return (full_path);
}
 
static void	free_the_array(char **array)
{
	int	i;
 
	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
 
static char	*search_in_dirs(char **dirs, char *cmd)
{
	char	*complete_path;
	int		i;
 
	i = 0;
	while (dirs[i])
	{
		complete_path = build_the_path(dirs[i], cmd);
		if (!complete_path)
			return (free_the_array(dirs), NULL);
		if (access(complete_path, F_OK | X_OK) == 0)
			return (free_the_array(dirs), complete_path);
		free(complete_path);
		i++;
	}
	return (free_the_array(dirs), NULL);
}
 
char	*find_the_cmd(char *cmd, t_shell *shell)
{
	char	**dirs;
	char	*path_init;
 
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_init = get_the_path(shell);
	if (!path_init)
		return (NULL);
	dirs = ft_split(path_init, ':');
	if (!dirs)
		return (NULL);
	return (search_in_dirs(dirs, cmd));
}
 