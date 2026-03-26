/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:02:05 by elibrahi          #+#    #+#             */
/*   Updated: 2026/03/26 19:19:04 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexer.h"

typedef struct s_shell	t_shell;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*rd_in;
	t_redir			*rd_out;
	struct s_cmd	*next;
}	t_cmd;

/* cmd.c */
t_cmd	*parse_cmd(t_token *tokens);
int		count_cmd(t_token *tokens);

/* parsing.c */
t_cmd	*parse_line(t_token *tokens);
t_cmd	*parse_pipe(t_token *tokens);

/* exec_redir.c */
t_redir	*c_new_redir(t_token_type type, char *file);
void	add_redir_back(t_redir **lst, t_redir *new);

/* utils_pars.c */
void	print_cmd(t_cmd *cmd);
void	print_redirs(t_redir *lst, char *label);
void	free_redirs(t_redir *lst);
void	free_cmd(t_cmd *cmd);
int		syntax_error(t_token *tokens);

/* utils.c */
int		redirection(t_token_type type);

/* arg.c */
void	remove_quotes(t_token *tokens);

/* var.c */
void	expand_tokens(t_token *tokens, t_shell *shell);

/* var2.c */
char	*append_char(char *result, char c);
char	*append_str(char *result, char *str);
char	*get_var_value(char *input, int *i, t_shell *shell);
char	*handle_dollar(char *word, int *i, char *result, t_shell *shell);

#endif
