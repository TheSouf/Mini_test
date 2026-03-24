/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:17:20 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/22 17:20:52 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
void	print_redirs(t_redir *lst, char *label)
{
	t_redir	*tmp;
 
	tmp = lst;
	printf("%s:\n", label);
	while (tmp)
	{
		printf("type = %d, file = %s\n", tmp->type, tmp->file);
		tmp = tmp->next;
	}
}
 
void	print_cmd(t_cmd *cmd)
{
	int	i;
 
	i = 0;
	if (!cmd)
	{
		printf("cmd = NULL\n");
		return ;
	}
	printf("___CMD___\n");
	while (cmd->argv && cmd->argv[i])
	{
		printf("argv[%d] = %s\n", i, cmd->argv[i]);
		i++;
	}
	print_redirs(cmd->rd_in, "input redirs");
	print_redirs(cmd->rd_out, "output redirs");
	printf("______________\n");
}
 
void	free_redirs(t_redir *lst)
{
	t_redir	*next;
 
	while (lst)
	{
		next = lst->next;
		if (lst->file)
			free(lst->file);
		free(lst);
		lst = next;
	}
}
 
/*
** Libere toute la liste chainee de t_cmd.
*/
void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;
	int		i;
 
	while (cmd)
	{
		next = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free_redirs(cmd->rd_in);
		free_redirs(cmd->rd_out);
		free(cmd);
		cmd = next;
	}
}
 
int	syntax_error(t_token *tokens)
{
	t_token	*prev;
 
	if (!tokens)
		return (0);
	prev = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!prev || !tokens->next)
				return (1);
			if (prev->type == PIPE)
				return (1);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
