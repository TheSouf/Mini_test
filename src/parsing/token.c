/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 04:17:42 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/13 17:30:58 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*c_new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	
	return (token);
}

void	add_token(t_token **lst, t_token *new)
{
	t_token	*tmp_token;
	
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp_token = *lst;
	while (tmp_token->next)
		tmp_token = tmp_token->next;
	tmp_token->next = new;
}

void	free_tokens(t_token *lst)
{
	t_token	*tmp_next;
	
	while (lst)
	{
		tmp_next = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp_next;
	}
}
