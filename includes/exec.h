/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:15:01 by sofkhali          #+#    #+#             */
/*   Updated: 2026/03/27 19:49:45 by sofkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_redir	t_redir;

/* builtins */
int		builtin_echo(char **args, t_shell *shell);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(char **args, t_shell *shell);
int		builtin_env(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_exit(char **args, t_shell *shell);

/* utils_builtin.c */
void	update_env_var(t_shell *shell, char *name, char *value);
void	init_shlvl(t_shell *shell);

/* exec_cmd.c */
int		is_builtin(char *name);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
void	execute_the_cmd(t_cmd *cmd, t_shell *shell);

/* exec_path.c */
char	*find_the_cmd(char *cmd, t_shell *shell);

/* exec_redir.c */
t_redir	*c_new_redir(t_token_type type, char *file);
void	add_redir_back(t_redir **lst, t_redir *new);
int		apply_the_redirs(t_redir *rd_in, t_redir *rd_out);

/* exec_process.c */
void	run_builtin_with_redirs(t_cmd *cmd, t_shell *shell);
void	run_child_processus(t_cmd *cmd, int i, int n,
			int (*pipe_fds)[2], t_shell *shell);
int		get_exit_status(int status);
void	wait_the_processes(pid_t *pids, int n, t_shell *shell);

/* exec_pipeline.c */
void	run_the_pipeline(t_cmd *cmds, t_shell *shell);

/* utils_env.c */
t_env	*env_new_node(char *name, char *value);
void	env_add_back(t_env **lst, t_env *new);
t_env	*env_find(t_env *lst, char *name);
void	env_free_list(t_env *lst);

/* utils_env2.c */
t_env	*env_init_from_envp(char **envp);
char	**env_to_array(t_env *lst);

#endif
