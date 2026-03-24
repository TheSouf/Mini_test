/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 04:20:51 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/22 17:21:07 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
static int	count_quoted_len(char *value, int *i)
{
	char	quote;
	int		len;
 
	quote = value[(*i)++];
	len = 0;
	while (value[*i] && value[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (value[*i])
		(*i)++;
	return (len);
}
 
static int	count_stripped_len(char *value)
{
	int	len;
	int	i;
 
	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			len += count_quoted_len(value, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
 
static void	fill_stripped(char *dst, char *value)
{
	int		i;
	int		j;
	char	quote;
 
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
		{
			quote = value[i++];
			while (value[i] && value[i] != quote)
				dst[j++] = value[i++];
			if (value[i])
				i++;
		}
		else
			dst[j++] = value[i++];
	}
	dst[j] = '\0';
}
 
static char	*strip_quotes(char *value)
{
	char	*result;
 
	result = malloc(sizeof(char) * (count_stripped_len(value) + 1));
	if (!result)
		return (NULL);
	fill_stripped(result, value);
	return (result);
}
 
/*
** Applique le quote removal sur tous les tokens WORD.
** A appeler apres expand_tokens() — les quotes servent a
** delimiter les zones d'expansion, puis sont supprimees ici.
*/
void	remove_quotes(t_token *tokens)
{
	char	*stripped;
 
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			stripped = strip_quotes(tokens->value);
			if (stripped)
			{
				free(tokens->value);
				tokens->value = stripped;
			}
		}
		tokens = tokens->next;
	}
}
