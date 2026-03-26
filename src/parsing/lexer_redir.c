/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 19:35:08 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:22:50 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redir_out(t_token **tokens, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		add_token(tokens, c_new_token(">>", APPEND));
		*i += 2;
	}
	else
	{
		add_token(tokens, c_new_token(">", REDIR_OUT));
		(*i)++;
	}
}

void	handle_redir_in(t_token **tokens, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		add_token(tokens, c_new_token("<<", HEREDOC));
		*i += 2;
	}
	else
	{
		add_token(tokens, c_new_token("<", REDIR_IN));
		(*i)++;
	}
}
