/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:14:53 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/21 22:49:00 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
 
typedef enum e_token_type
{
	WORD,		// 0 = commande, argument, fichier
	PIPE,		// 1 = |
	REDIR_IN,	// 2 = <
	REDIR_OUT,	// 3 = >
	APPEND,		// 4 = >>
	HEREDOC,	// 5 = <<
}	t_token_type;
 
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token	*c_new_token(char *value, t_token_type type);
void	add_token(t_token **lst, t_token *new);
void	free_tokens(t_token *lst);

t_token	*lexer(char *input);

void	handle_redir_out(t_token **tokens, char *input, int *i);
void	handle_redir_in(t_token **tokens, char *input, int *i);
 
#endif
 