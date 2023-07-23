/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:50:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 21:11:43 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data	g_data;
char	*g_argv[5];

void	execute_cd_test(char *name, char *path)
{
	char	*pwd;

	printf("TEST: %s\n", name);
	pwd = NULL;
	ft_create_pwd_value(&pwd);
	printf("Current pwd: %s\n", pwd);
	free(pwd);
	g_argv[1] = path;
	ft_cd(g_argv, g_data.env_table);
	ft_create_pwd_value(&pwd);
	printf("After change: %s\n\n", pwd);
	free(pwd);
}

void	test_builtin_cd(void)
{
	printf("**\tTEST BUILTIN CD\t**\n\n");
	test_setup_data();
	g_argv[0] = "cd";
	g_argv[2] = NULL;
	execute_cd_test("Existing path /usr", "/usr");
	execute_cd_test("No arg = $HOME", NULL);
	execute_cd_test("Double dot", "..");
	execute_cd_test("Single dot", ".");
	execute_cd_test("Error: not existing", "/garbage");
	g_argv[2] = "garbage";
	g_argv[3] = NULL;
	execute_cd_test("Error: too many args", "/usr");
}