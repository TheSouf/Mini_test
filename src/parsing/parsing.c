/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:02:25 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/26 19:36:29 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*cut_segment(t_token *tok, t_token **next)
{
	while (tok->next && tok->next->type != PIPE)
		tok = tok->next;
	if (!tok->next)
	{
		*next = NULL;
		return (NULL);
	}
	*next = tok->next->next;
	tok->next->next = NULL;
	tok->next = NULL;
	return (tok);
}

static int	chain_cmd(t_cmd **first, t_cmd **last, t_cmd *new)
{
	if (!new)
		return (-1);
	if (!*first)
		*first = new;
	else
		(*last)->next = new;
	*last = new;
	return (0);
}

t_cmd	*parse_pipe(t_token *tokens)
{
	t_cmd	*first;
	t_cmd	*last;
	t_token	*seg;
	t_token	*cut;
	t_token	*next;

	first = NULL;
	last = NULL;
	seg = tokens;
	while (seg)
	{
		cut = cut_segment(seg, &next);
		if (chain_cmd(&first, &last, parse_cmd(seg)) < 0)
		{
			free_cmd(first);
			return (NULL);
		}
		if (!cut)
			break ;
		cut->next = next;
		seg = next;
	}
	return (first);
}

t_cmd	*parse_line(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	if (syntax_error(tokens))
	{
		write(2, "minishell: syntax error near `|'\n", 33);
		return (NULL);
	}
	return (parse_pipe(tokens));
}
