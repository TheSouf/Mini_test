/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:59:57 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/26 19:37:46 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quoted(char *input, int *pos)
{
	char	quote;

	quote = input[*pos];
	(*pos)++;
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	if (input[*pos] == quote)
		(*pos)++;
}

static char	*handle_word(char *input, int *pos)
{
	int	start;

	start = *pos;
	while (input[*pos] && input[*pos] != ' ' && input[*pos] != '|'
		&& input[*pos] != '<' && input[*pos] != '>')
	{
		if (input[*pos] == '\'' || input[*pos] == '"')
			skip_quoted(input, pos);
		else
			(*pos)++;
	}
	return (ft_substr(input, start, *pos - start));
}

static int	check_unclosed_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] != quote)
			{
				write(2, "minishell: unclosed quotes\n", 27);
				return (1);
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}

static void	add_word_token(t_token **tokens, char *input, int *i)
{
	char	*word;

	word = handle_word(input, i);
	if (word)
	{
		add_token(tokens, c_new_token(word, WORD));
		free(word);
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;

	if (check_unclosed_quote(input))
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, c_new_token("|", PIPE));
			i++;
		}
		else if (input[i] == '>')
			handle_redir_out(&tokens, input, &i);
		else if (input[i] == '<')
			handle_redir_in(&tokens, input, &i);
		else
			add_word_token(&tokens, input, &i);
	}
	return (tokens);
}
