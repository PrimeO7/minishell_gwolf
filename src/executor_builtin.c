/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:47:58 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/14 17:28:20 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_builtin.c
 * @brief Functions to handle execution of built-ins.
 */

#include "mod_executor.h"

/**
 * @brief Verify if given cmd is a builtin.
 * 
 * Compare including '\0' to be sure it is 
 * the cmd and not a str with same head.
 * @param arg 		Cmd str to check.
 * @return true 	Built-in found.
 * @return false 	Built-in not found.
 */
bool	ft_check_builtin(char *arg)
{
	if (!ft_strncmp(arg, "cd", 3) || !ft_strncmp(arg, "echo", 5)
		|| !ft_strncmp(arg, "env", 4) || !ft_strncmp(arg, "exit", 5)
		|| !ft_strncmp(arg, "export", 7) || !ft_strncmp(arg, "pwd", 4)
		|| !ft_strncmp(arg, "unset", 6))
		return (true);
	return (false);
}

/**
 * @brief Handle built-in execution.
 * 
 * Direct built-in call when it is a single cmd.
 * Creation of child process when part of a pipe.
 * @param piped 	Bool to differentiate if part of pipe.
 * @param cmd 		Cmd to be processed which is a built-in.
 * @param data 		Data struct containing env.
 * @return t_err 	ERR_CLOSE, ERR_FORK, SUCCESS
 */
t_err	ft_execute_builtin(bool piped, t_cmd *cmd, t_data *data)
{
	t_err	err;

	if (piped)
	{
		err = ft_create_child(cmd, data, true);
		if (err != SUCCESS)
			return (err);
	}
	else
	{
		err = ft_set_fd_builtin(cmd);
		if (err != SUCCESS)
			return (err);
		ft_choose_builtin(cmd, data);
	}
	return (SUCCESS);
}

/**
 * @brief Set the file descriptors for execution of scmd builtin.
 * 
 * @param cmd 		Current cmd.
 * @return t_err 	ERR_CLOSE, SUCCESS
 */
t_err	ft_set_fd_builtin(t_cmd *cmd)
{
	t_err	err;

	if (cmd->fd_out >= 0)
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_out);
		else
			ft_replace_fd(0, cmd->fd_out);
		err = ft_close(&cmd->fd_out);
		if (err != SUCCESS)
			return (err);
	}
	err = ft_close(&cmd->fd_in);
	return (err);
}

/**
 * @brief Call suitable built-in.
 * 
 * @param cmd 	Cmd containing built-in call and its args.
 * @param data 	Data struct containing env.
 */
void	ft_choose_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(cmd->args, data->env_table);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env(data->env_table);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(cmd->args, data->env_table);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(cmd->args, data->env_table);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(cmd->args, data->env_table);
}
