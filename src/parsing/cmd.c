/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 04:20:38 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/26 19:39:20 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words(t_token *tok)
{
	int	n;

	n = 0;
	while (tok)
	{
		if (tok->type == WORD)
			n++;
		tok = tok->next;
	}
	return (n);
}

int	count_cmd(t_token *tokens)
{
	t_token	*tok;
	int		count;

	if (!tokens)
		return (0);
	count = 1;
	tok = tokens;
	while (tok)
	{
		if (tok->type == PIPE)
			count++;
		tok = tok->next;
	}
	return (count);
}

static t_token	*handle_redir_tok(t_cmd *cmd, t_token *tok)
{
	if (!tok->next)
		return (NULL);
	if (tok->type == REDIR_IN || tok->type == HEREDOC)
		add_redir_back(&cmd->rd_in,
			c_new_redir(tok->type, tok->next->value));
	else
		add_redir_back(&cmd->rd_out,
			c_new_redir(tok->type, tok->next->value));
	return (tok->next->next);
}

static void	fill_cmd(t_cmd *cmd, t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == WORD)
		{
			cmd->argv[i++] = ft_strdup(tok->value);
			tok = tok->next;
		}
		else
			tok = handle_redir_tok(cmd, tok);
	}
	cmd->argv[i] = NULL;
}

t_cmd	*parse_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->rd_in = NULL;
	cmd->rd_out = NULL;
	cmd->next = NULL;
	cmd->argv = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	fill_cmd(cmd, tokens);
	return (cmd);
}
