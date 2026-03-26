/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 04:21:46 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/26 19:40:00 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_word(char *word, t_shell *shell)
{
	char	*result;
	int		i;
	int		in_single;

	result = ft_strdup("");
	i = 0;
	in_single = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			in_single = !in_single;
			result = append_char(result, '\'');
		}
		else if (word[i] == '$' && !in_single)
		{
			result = handle_dollar(word, &i, result, shell);
			continue ;
		}
		else
			result = append_char(result, word[i]);
		i++;
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			expanded = expand_word(tokens->value, shell);
			if (expanded)
			{
				free(tokens->value);
				tokens->value = expanded;
			}
		}
		tokens = tokens->next;
	}
}
