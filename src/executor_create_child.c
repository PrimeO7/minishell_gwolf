/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_create_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:22:17 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 19:16:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_create_child.c
 * @brief Functions to create child processes.
 */

#include "mod_executor.h"

/**
 * @brief Distinguishes between the position of the command
 * to be executed and creates the pertinent child.
 *
 * @param cmd 		Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_FORK, SUCCESS
 */
t_err	ft_create_child(t_cmd *cmd, t_data *data, bool builtin)
{
	t_err	err;

	ft_signal_setup(SIGINT, SIG_STD);
	ft_signal_setup(SIGQUIT, SIG_STD);
	if (cmd->index == 0)
		err = ft_raise_first(cmd, data, builtin);
	else if (cmd->index == cmd->cmd_num - 1)
		err = ft_raise_last(cmd, data, builtin);
	else
		err = ft_raise_middle(cmd, data, builtin);
	return (err);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the first cmd of the pipe.
 *
 * The parent closes the write end fd of the pipe (fd_pipe[1]).
 * @param cmd 		Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_FORK, SUCCESS
 */
t_err	ft_raise_first(t_cmd *cmd, t_data *data, bool builtin)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		ft_close(&cmd->fd_pipe[1]);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_firstborn(cmd, data, builtin);
	else
	{
		ft_close(&cmd->fd_pipe[1]);
		ft_close(&cmd->fd_out);
		ft_close(&cmd->fd_in);
	}
	return (SUCCESS);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the last cmd of the pipe.
 *
 * @param cmd 		Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_FORK, SUCCESS
 */
t_err	ft_raise_last(t_cmd *cmd, t_data *data, bool builtin)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		ft_close(&cmd->fd_pipe[1]);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_lastborn(cmd, data, builtin);
	else
		ft_close_iopp(cmd);
	return (SUCCESS);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by a cmd between the first
 * and last cmd of the pipe.
 *
 * The parent closes the write end fd of the pipe (fd_pipe[1]).
 * @param cmd 	Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_FORK, SUCCESS
 */
t_err	ft_raise_middle(t_cmd *cmd, t_data *data, bool builtin)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		ft_close(&cmd->fd_pipe[1]);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_middle_child(cmd, data, builtin);
	else
	{
		ft_close(&cmd->fd_pipe[1]);
		ft_close_iopp(cmd);
	}
	return (SUCCESS);
}
