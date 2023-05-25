/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/24 19:15:49 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_failure(data, ERR_MALLOC);
	if (ft_setup_env(data) != SUCCESS)
		printf("NO\n");
	ft_hashtable_print(data->env_table);
	ft_hashtable_destroy(data->env_table);
	free(data);
}