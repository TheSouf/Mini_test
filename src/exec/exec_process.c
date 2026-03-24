/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:29:04 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/22 17:20:08 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
static void	close_all_pipes(int (*pipe_fds)[2], int n, int fd_read, int fd_write)
{
	int	i;
 
	i = 0;
	while (i < n - 1)
	{
		if (pipe_fds[i][0] != fd_read)
			close(pipe_fds[i][0]);
		if (pipe_fds[i][1] != fd_write)
			close(pipe_fds[i][1]);
		i++;
	}
}
 
void	run_child_processus(t_cmd *cmd, int i, int n,
			int (*pipe_fds)[2], t_shell *shell)
{
	int	fd_read;
	int	fd_write;
 
	if (i == 0)
		fd_read = STDIN_FILENO;
	else
		fd_read = pipe_fds[i - 1][0];
	if (i == n - 1)
		fd_write = STDOUT_FILENO;
	else
		fd_write = pipe_fds[i][1];
	close_all_pipes(pipe_fds, n, fd_read, fd_write);
	if (fd_read != STDIN_FILENO)
	{
		dup2(fd_read, STDIN_FILENO);
		close(fd_read);
	}
	if (fd_write != STDOUT_FILENO)
	{
		dup2(fd_write, STDOUT_FILENO);
		close(fd_write);
	}
	execute_the_cmd(cmd, shell);
}
 
int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}
 
void	wait_the_processes(pid_t *pids, int n, t_shell *shell)
{
	int	i;
	int	status;
 
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
			shell->last_exit_code = get_exit_status(status);
		i++;
	}
}
 
void	run_builtin_with_redirs(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
 
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_the_redirs(cmd->rd_in, cmd->rd_out) < 0)
		shell->last_exit_code = 1;
	else
		shell->last_exit_code = exec_builtin(cmd, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
