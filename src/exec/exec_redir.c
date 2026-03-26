/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:28:35 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:33:41 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*c_new_redir(t_token_type type, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	if (!r->file)
	{
		free(r);
		return (NULL);
	}
	r->next = NULL;
	return (r);
}

void	add_redir_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (fd);
}

static int	open_outfile(char *file, int append)
{
	int	fd;
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	return (fd);
}

int	apply_the_redirs(t_redir *rd_in, t_redir *rd_out)
{
	int		fd;
	t_redir	*r;

	r = rd_out;
	while (r)
	{
		fd = open_outfile(r->file, r->type == APPEND);
		if (fd < 0)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
	r = rd_in;
	while (r)
	{
		fd = open_infile(r->file);
		if (fd < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		r = r->next;
	}
	return (0);
}
