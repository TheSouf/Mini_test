/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:32:12 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/27 20:46:41 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_sigint(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_kill_text(0, rl_end);
	rl_redisplay();
}

static void	init_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	struct sigaction	ignore_quit;
	sigemptyset(&ignore_quit.sa_mask);
	ignore_quit.sa_handler = SIG_IGN;
	ignore_quit.sa_flags = 0;
	sigaction(SIGQUIT, &ignore_quit, NULL);
}

static void	run_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return ;
	expand_tokens(tokens, shell);
	remove_quotes(tokens);
	cmds = parse_line(tokens);
	free_tokens(tokens);
	if (!cmds)
		return ;
	run_the_pipeline(cmds, shell);
	free_cmd(cmds);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		run_line(line, shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env_list = env_init_from_envp(envp);
	shell.last_exit_code = 0;
	if (!shell.env_list)
	{
		write(2, "minishell: failed to init env\n", 30);
		return (1);
	}
	init_shlvl(&shell);
	init_signals();
	shell_loop(&shell);
	env_free_list(shell.env_list);
	return (shell.last_exit_code);
}
