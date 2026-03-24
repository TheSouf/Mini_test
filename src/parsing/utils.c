/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 04:21:40 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/13 17:31:13 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}
