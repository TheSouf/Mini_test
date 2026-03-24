/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:33:45 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/22 20:24:44 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
static int	count_the_cmds(t_cmd *cmds)
{
	int		n;
	t_cmd	*cur;
 
	n = 0;
	cur = cmds;
	while (cur)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}
 
static int	open_the_pipes(int (*pipe_fds)[2], int n)
{
	int	i;
 
	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
 
static void	close_the_pipes(int (*pipe_fds)[2], int n)
{
	int	i;
 
	i = 0;
	while (i < n - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}
 
static int	fork_the_processes(t_cmd *cmds, int (*pipe_fds)[2],
				pid_t *pids, t_shell *shell)
{
	t_cmd	*cur;
	int		i;
	int		n;
 
	n = count_the_cmds(cmds);
	i = 0;
	cur = cmds;
	while (cur)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (-1);
		if (pids[i] == 0)
			run_child_processus(cur, i, n, pipe_fds, shell);
		cur = cur->next;
		i++;
	}
	return (0);
}
 
void	run_the_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		n;
	int		(*pipe_fds)[2];
	pid_t	*pids;
 
	if (!cmds || !cmds->argv || !cmds->argv[0])
		return ;
	if (!cmds->next && is_builtin(cmds->argv[0]))
	{
		run_builtin_with_redirs(cmds, shell);
		return ;
	}
	n = count_the_cmds(cmds);
	pipe_fds = malloc(sizeof(int[2]) * n);
	pids = malloc(sizeof(pid_t) * n);
	if (!pipe_fds || !pids)
		return (free(pipe_fds), free(pids), (void)0);
	if (open_the_pipes(pipe_fds, n) == -1)
		return (free(pipe_fds), free(pids), (void)0);
	if (fork_the_processes(cmds, pipe_fds, pids, shell) == -1)
		return (free(pipe_fds), free(pids), (void)0);
	close_the_pipes(pipe_fds, n);
	wait_the_processes(pids, n, shell);
	free(pipe_fds);
	free(pids);
}
