/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_executor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:32 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/08 11:16:05 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_EXECUTOR_H
# define MOD_EXECUTOR_H

/* ====== Includes ====== */

# include "mod_handle_input.h"

/* ====== Structs ====== */

/* ====== Functions ====== */

// cmd handling
void	ft_init_exec(t_cmd *cmd);
t_err	ft_create_pipes(t_cmd *cmd);
t_err	ft_execute_cmds(t_cmd *cmd, char **envp, char **paths, t_data *data);
t_err	ft_process_cmd(t_cmd *cmd, t_err err, char **envp, t_data *data);

// create child processes
t_err	ft_create_child(t_cmd *cmd, char **envp, t_data *data, bool builtin);
t_err	ft_raise_first(t_cmd *cmd, char **envp, t_data *data, bool builtin);
t_err	ft_raise_last(t_cmd *cmd, char **envp, t_data *data, bool builtin);
t_err	ft_raise_middle(t_cmd *cmd, char **envp, t_data *data, bool builtin);

// child behaviour
void	ft_firstborn(t_cmd *cmd, char **envp, t_data *data, bool builtin);
void	ft_lastborn(t_cmd *cmd, char **envp, t_data *data, bool builtin);
void	ft_middle_child(t_cmd *cmd, char **envp, t_data *data, bool builtin);

// heredoc
t_err	ft_handle_heredoc(t_cmd *cmd);
t_err	ft_create_heredoc(t_cmd *cmd, char *delim, int curr_delim);
t_err	ft_name_heredoc(int index, char **name);
t_err	ft_initiate_heredoc(int index, char **name, int *fd);
t_err	ft_heredoc_fate(t_cmd *cmd, char *name, int fd, int curr_delim);

// cleanup
void	ft_cleanup_cmd(t_cmd *cmd);
t_err	ft_unlink_heredoc(char *name, t_err err);
t_err	ft_close(int fd);
t_err	ft_plug_pipe(t_cmd *cmd, bool close_read_end);

// utils
t_err	ft_check_cmd_access(char **args, char **cmd_paths);
t_err	ft_prefix_path(char **args, char **cmd_paths);
t_err	ft_get_path(char **envp, char ***paths);
t_err	ft_replace_fd(int input_fd, int output_fd);
t_err	ft_wait_for_babies(t_cmd *cmd);

// builtins
bool	ft_check_builtin(char *arg);
t_err	ft_execute_builtin(bool piped, t_cmd *cmd, char **envp, t_data *data);
void	ft_choose_builtin(t_cmd *cmd, t_data *data);

// include from mod_cleanup
void	ft_free_str_arr(char **arr);

// include from mod_builtin
t_err	ft_cd(char **argv, t_hashtable *env_tab);
t_err	ft_echo(char **argv);
t_err	ft_pwd(void);
t_err	ft_export(char **argv, t_hashtable *env_tab);
t_err	ft_unset(char **argv, t_hashtable *env_tab);
t_err	ft_env(t_hashtable *env_tab);
t_err	ft_exit(char **argv, t_hashtable *env_tab);

#endif