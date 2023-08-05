/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_executor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:32 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/05 16:31:35 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_EXECUTOR_H
# define MOD_EXECUTOR_H

/* ====== Includes ====== */

# include "mod_handle_input.h"

/* ====== Structs ====== */

/* ====== Functions ====== */

void	ft_init_exec(t_cmd *cmd);
t_err	ft_execute_cmds(t_cmd *cmd, char **envp, char **paths);

void	ft_create_child(t_cmd *cmd, char **envp);

// heredoc
t_err	ft_handle_heredoc(t_cmd *cmd);
t_err	ft_create_heredoc(t_cmd *cmd, char *delim, int curr_delim);
t_err	ft_name_heredoc(int index, char *name);
t_err	ft_initiate_heredoc(int index, char *name, int *fd);
t_err	ft_heredoc_fate(t_cmd *cmd, char *name, int fd, int curr_delim);

// cleanup
t_err	ft_unlink_heredoc(char *name, t_err err);
t_err	ft_close(int fd);

// utils
t_err	ft_check_cmd_access(char **args, char **cmd_paths);
t_err	ft_prefix_path(char **args, char **cmd_paths);
t_err	ft_get_path(char **envp, char ***paths);

#endif