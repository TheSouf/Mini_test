/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 22:13:44 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/26 19:36:59 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*append_str(char *result, char *str)
{
	char	*tmp;

	if (!str)
		return (result);
	tmp = ft_strjoin(result, str);
	free(result);
	free(str);
	return (tmp);
}

char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

char	*get_var_value(char *input, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	t_env	*node;

	if (input[*i] == '?')
		return ((*i)++, ft_itoa(shell->last_exit_code));
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	name = ft_substr(input, start, *i - start);
	if (!name)
		return (NULL);
	node = env_find(shell->env_list, name);
	free(name);
	if (!node || !node->value)
		return (ft_strdup(""));
	return (ft_strdup(node->value));
}

char	*handle_dollar(char *word, int *i, char *result, t_shell *shell)
{
	(*i)++;
	if (!word[*i] || word[*i] == ' ' || word[*i] == '\'')
		return (append_char(result, '$'));
	return (append_str(result, get_var_value(word, i, shell)));
}
