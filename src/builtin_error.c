/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 21:41:04 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_cd_error(t_err err, char *oldpwd, char *path)
{
	if (oldpwd)
		free(oldpwd);
	if (err == ERR_ARGCOUNT)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (err == ERR_NOT_FOUND)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (err == ERR_MALLOC)
		ft_putstr_fd("minishell: cd: Malloc failed\n", 2);
	else if (err == ERR_CHDIR_FAIL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
	return (err);
}
