/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:27:12 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:35:33 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0 || ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*n;

	n = cmd->argv[0];
	if (ft_strcmp(n, "echo") == 0)
		return (builtin_echo(cmd->argv, shell));
	if (ft_strcmp(n, "cd") == 0)
		return (builtin_cd(cmd->argv, shell));
	if (ft_strcmp(n, "pwd") == 0)
		return (builtin_pwd(cmd->argv, shell));
	if (ft_strcmp(n, "env") == 0)
		return (builtin_env(cmd->argv, shell));
	if (ft_strcmp(n, "export") == 0)
		return (builtin_export(cmd->argv, shell));
	if (ft_strcmp(n, "unset") == 0)
		return (builtin_unset(cmd->argv, shell));
	return (builtin_exit(cmd->argv, shell));
}

static void	cmd_not_found(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": command not found", 2);
}

static void	exec_external(char *path, t_cmd *cmd, t_shell *shell)
{
	char	**envp;

	envp = env_to_array(shell->env_list);
	execve(path, cmd->argv, envp);
	perror("execve");
	exit(126);
}

void	execute_the_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (apply_the_redirs(cmd->rd_in, cmd->rd_out) < 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, shell));
	path = find_the_cmd(cmd->argv[0], shell);
	if (!path)
	{
		cmd_not_found(cmd->argv[0]);
		exit(127);
	}
	if (access(path, F_OK) != 0)
	{
		cmd_not_found(cmd->argv[0]);
		free(path);
		exit(127);
	}
	exec_external(path, cmd, shell);
}
