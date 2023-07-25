/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:11:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 23:46:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_export.c
 * @brief Implementation of builtin export.
 */
#include "mod_builtin.h"

/**
 * @brief Export a variable into environment.
 *
 * Check arg size with ft_get_array_size().
 * If no arg is given ft_print_env_sorted().
 * For all args try to insert them into environment with
 * ft_check_and_update_env(). If error is encountered print
 * error with ft_export_error(). Continue for all other args.
 *
 * @param argv NULL terminated args.
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_INVALID_NAME
 */
t_err	ft_export(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	size_t	i;

	size = 0;
	err = ft_get_array_size(argv, &size);
	if (err != SUCCESS)
		return (err);
	if (size == 1)
		return (ft_print_env_sorted(env_tab));
	i = 1;
	while (argv[i])
	{
		err = ft_check_and_update_env(argv[i], env_tab);
		if (err != SUCCESS)
			ft_export_error(err, argv[i]);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Print ASCII sorted environment.
 *
 * Create envp with ft_envp_create().
 * If error print with ft_export_error().
 * Use ft_quicksort_string() to sort envp.
 * Print env_strings with ft_pretty_print_envp().
 * Destroy envp with ft_envp_destroy().
 *
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_MALLOC, ERR_INVALID_NAME.
 */
t_err	ft_print_env_sorted(t_hashtable *env_tab)
{
	char	**envp;
	t_err	err;

	envp = NULL;
	err = ft_envp_create(env_tab, &envp);
	if (err != SUCCESS)
		return (ft_export_error(err, NULL));
	ft_quicksort_strings(envp, 0, env_tab->num_elements - 1);
	err = ft_pretty_print_envp(envp, env_tab->num_elements);
	if (err != SUCCESS)
		return (ft_export_error(err, NULL));
	err = ft_envp_destroy(&envp);
	return (err);
}

/**
 * @brief Print env_str in pretty from.
 *
 * Print "export ".
 * Print key of the env_var.
 * If followed by a value print equals sign and value enclosed in double quotes.
 *
 * @param envp Array with all env_str.
 * @param size Size of pointer array.
 * @return t_err SUCCESS, ERR_INVALID_NAME.
 */
t_err	ft_pretty_print_envp(char **envp, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	keylen;
	t_err	err;

	i = 0;
	while (i < size)
	{
		keylen = 0;
		err = ft_get_env_keylen(envp[i], &keylen);
		if (err != SUCCESS)
			return (err);
		ft_putstr_fd("export ", 1);
		j = 0;
		while (j < keylen)
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		if (envp[i][keylen] == '=')
			printf("=\"%s\"", envp[i] + keylen + 1);
		printf("\n");
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Check env_str for valid key. If so update environment.
 *
 * Check key with ft_get_env_keylen().
 * If valid ft_strdup() the given env_str.
 * Then update environment with ft_update_env_var().
 *
 * @param str Env_str to check.
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_INVALID_NAME, ERR_MALLOC, ERR_EMPTY,
 * ERR_HT_NO_INSERT, ERR_HT_NO_SWAP.
 */
t_err	ft_check_and_update_env(char *str, t_hashtable *env_tab)
{
	size_t	keylen;
	t_err	err;
	char	*temp;

	keylen = 0;
	err = ft_get_env_keylen(str, &keylen);
	if (err != SUCCESS)
		return (err);
	temp = ft_strdup(str);
	if (!temp)
		return (ERR_MALLOC);
	err = ft_update_env_var(env_tab, temp, keylen);
	if (err != SUCCESS)
	{
		free(temp);
		return (err);
	}
	return (SUCCESS);
}
