/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:16:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/27 12:28:30 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_utils3.c
 * @brief Helper functions for executor
 */

#include "mod_executor.h"

/**
 * @brief Sets exit status if last cmd of a pipeline
 * exited with ERR_UNKNOWN_CMD, ERR_NO_DIR or ERR_DIR.
 * 
 * @param err ERR_UNKNOWN_CMD, ERR_NO_DIR or ERR_DIR
 */
void	ft_set_exit_status(t_err err)
{
	if (err == ERR_UNKNOWN_CMD || err == ERR_NO_DIR)
		g_status = 127;
	else if (err == ERR_DIR)
		g_status = 126;
}
